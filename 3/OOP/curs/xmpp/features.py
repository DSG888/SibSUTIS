from .protocol import *

REGISTER_DATA_RECEIVED = "REGISTER DATA RECEIVED"

def _discover(disp, ns, jid, node=None, fb2b=0, fb2a=1):
	iq = Iq(to=jid, typ="get", queryNS=ns)
	if node:
		iq.setQuerynode(node)
	rep = disp.SendAndWaitForResponse(iq)
	if fb2b and not isResultNode(rep):
		rep = disp.SendAndWaitForResponse(Iq(to=jid, typ="get", queryNS=NS_BROWSE)) # Fallback to browse
	if fb2a and not isResultNode(rep):
		rep = disp.SendAndWaitForResponse(Iq(to=jid, typ="get", queryNS=NS_AGENTS)) # Fallback to agents
	if isResultNode(rep):
		return [n for n in rep.getQueryPayload() if isinstance(n, Node)]
	return []

def discoverItems(disp, jid, node=None):
	ret = []
	for i in _discover(disp, NS_DISCO_ITEMS, jid, node):
		if i.getName() == "agent" and i.getTag("name"):
			i.setAttr("name", i.getTagData("name"))
		ret.append(i.attrs)
	return ret

def discoverInfo(disp, jid, node=None):
	identities, features = [], []
	for i in _discover(disp, NS_DISCO_INFO, jid, node):
		if i.getName() == "identity":
			identities.append(i.attrs)
		elif i.getName() == "feature":
			features.append(i.getAttr("var"))
		elif i.getName() == "agent":
			if i.getTag("name"):
				i.setAttr("name", i.getTagData("name"))
			if i.getTag("description"):
				i.setAttr("name", i.getTagData("description"))
			identities.append(i.attrs)
			if i.getTag("groupchat"):
				features.append(NS_GROUPCHAT)
			if i.getTag("register"):
				features.append(NS_REGISTER)
			if i.getTag("search"):
				features.append(NS_SEARCH)
	return identities, features

def getRegInfo(disp, host, info={}, sync=True):
	iq = Iq("get", NS_REGISTER, to=host)
	for i in info.keys():
		iq.setTagData(i, info[i])
	if sync:
		resp = disp.SendAndWaitForResponse(iq)
		_ReceivedRegInfo(disp.Dispatcher, resp, host)
		return resp
	else:
		disp.SendAndCallForResponse(iq, _ReceivedRegInfo, {"agent": host})

def _ReceivedRegInfo(con, resp, agent):
	iq = Iq("get", NS_REGISTER, to=agent)
	if not isResultNode(resp):
		return None
	df = resp.getTag("query", namespace=NS_REGISTER).getTag("x", namespace=NS_DATA)
	if df:
		con.Event(NS_REGISTER, REGISTER_DATA_RECEIVED, (agent, DataForm(node=df)))
		return None
	df = DataForm(typ="form")
	for i in resp.getQueryPayload():
		if not isinstance(i, Iq):
			pass
		elif i.getName() == "instructions":
			df.addInstructions(i.getData())
		else:
			df.setField(i.getName()).setValue(i.getData())
	con.Event(NS_REGISTER, REGISTER_DATA_RECEIVED, (agent, df))

def register(disp, host, info):
	iq = Iq("set", NS_REGISTER, to=host)
	if not isinstance(info, dict):
		info = info.asDict()
	for i in info.keys():
		iq.setTag("query").setTagData(i, info[i])
	resp = disp.SendAndWaitForResponse(iq)
	if isResultNode(resp):
		return 1

def unregister(disp, host):
	resp = disp.SendAndWaitForResponse(Iq("set", NS_REGISTER, to=host, payload=[Node("remove")]))
	if isResultNode(resp):
		return 1

def changePasswordTo(disp, newpassword, host=None):
	if not host:
		host = disp._owner.Server
	resp = disp.SendAndWaitForResponse(Iq("set", NS_REGISTER, to=host, payload=[Node("username", payload=[disp._owner.User]), Node("password", payload=[newpassword])]))
	if isResultNode(resp):
		return 1

def getPrivacyLists(disp):
	dict = {"lists": []}
	try:
		resp = disp.SendAndWaitForResponse(Iq("get", NS_PRIVACY))
		if not isResultNode(resp):
			return None
		for list in resp.getQueryPayload():
			if list.getName() == "list":
				dict["lists"].append(list.getAttr("name"))
			else:
				dict[list.getName()] = list.getAttr("name")
	except Exception:
		pass
	else:
		return dict

def getPrivacyList(disp, listname):
	try:
		resp = disp.SendAndWaitForResponse(Iq("get", NS_PRIVACY, payload=[Node("list", {"name": listname})]))
		if isResultNode(resp):
			return resp.getQueryPayload()[0]
	except Exception:
		pass

def setActivePrivacyList(disp, listname=None, typ="active"):
	if listname:
		attrs = {"name": listname}
	else:
		attrs = {}
	resp = disp.SendAndWaitForResponse(Iq("set", NS_PRIVACY, payload=[Node(typ, attrs)]))
	if isResultNode(resp):
		return 1

def setDefaultPrivacyList(disp, listname=None):
	return setActivePrivacyList(disp, listname, "default")

def setPrivacyList(disp, list):
	resp = disp.SendAndWaitForResponse(Iq("set", NS_PRIVACY, payload=[list]))
	if isResultNode(resp):
		return 1

def delPrivacyList(disp, listname):
	resp = disp.SendAndWaitForResponse(Iq("set", NS_PRIVACY, payload=[Node("list", {"name": listname})]))
	if isResultNode(resp):
		return 1
