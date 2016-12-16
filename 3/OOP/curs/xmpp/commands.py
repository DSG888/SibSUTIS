from .plugin import PlugIn
from .protocol import *

class Commands(PlugIn):
	def __init__(self, browser):
		PlugIn.__init__(self)
		DBG_LINE = "commands"
		self._exported_methods = []
		self._handlers = {"": {}}
		self._browser = browser

	def plugin(self, owner):
		owner.RegisterHandler("iq", self._CommandHandler, typ="set", ns=NS_COMMANDS)
		owner.RegisterHandler("iq", self._CommandHandler, typ="get", ns=NS_COMMANDS)
		self._browser.setDiscoHandler(self._DiscoHandler, node=NS_COMMANDS, jid="")

	def plugout(self):
		self._owner.UnregisterHandler("iq", self._CommandHandler, ns=NS_COMMANDS)
		for jid in self._handlers:
			self._browser.delDiscoHandler(self._DiscoHandler, node=NS_COMMANDS)

	def _CommandHandler(self, conn, request):
		jid = str(request.getTo())
		try:
			node = request.getTagAttr("command", "node")
		except Exception:
			conn.send(Error(request, ERR_BAD_REQUEST))
			raise NodeProcessed()
		if jid in self._handlers:
			if node in self._handlers[jid]:
				self._handlers[jid][node]["execute"](conn, request)
			else:
				conn.send(Error(request, ERR_ITEM_NOT_FOUND))
				raise NodeProcessed()
		elif node in self._handlers[""]:
			self._handlers[""][node]["execute"](conn, request)
		else:
			conn.send(Error(request, ERR_ITEM_NOT_FOUND))
			raise NodeProcessed()

	def _DiscoHandler(self, conn, request, typ):
		if typ == "items":
			list = []
			items = []
			jid = str(request.getTo())
			if jid in self._handlers:
				for each in self._handlers[jid].keys():
					items.append((jid, each))
			else:
				for each in self._handlers[""].keys():
					items.append(("", each))
			if items:
				for each in items:
					i = self._handlers[each[0]][each[1]]["disco"](conn, request, "list")
					if i != None:
						list.append(Node(tag="item", attrs={"jid": i[0], "node": i[1], "name": i[2]}))
				iq = request.buildReply("result")
				if request.getQuerynode():
					iq.setQuerynode(request.getQuerynode())
				iq.setQueryPayload(list)
				conn.send(iq)
			else:
				conn.send(Error(request, ERR_ITEM_NOT_FOUND))
			raise NodeProcessed()
		if typ == "info":
			return {"ids": [{"category": "automation", "type": "command-list"}], "features": []}

	def addCommand(self, name, cmddisco, cmdexecute, jid=""):
		if jid not in self._handlers:
			self._handlers[jid] = {}
			self._browser.setDiscoHandler(self._DiscoHandler, node=NS_COMMANDS, jid=jid)
		if name in self._handlers[jid]:
			raise NameError("Command Exists")
		self._handlers[jid][name] = {"disco": cmddisco, "execute": cmdexecute}
		self._browser.setDiscoHandler(cmddisco, node=name, jid=jid)

	def delCommand(self, name, jid=""):
		if jid not in self._handlers:
			raise NameError("Jid not found")
		if name not in self._handlers[jid]:
			raise NameError("Command not found")
		command = self.getCommand(name, jid)["disco"]
		del self._handlers[jid][name]
		self._browser.delDiscoHandler(command, node=name, jid=jid)

	def getCommand(self, name, jid=""):
		if jid not in self._handlers:
			raise NameError("Jid not found")
		if name not in self._handlers[jid]:
			raise NameError("Command not found")
		return self._handlers[jid][name]

class Command_Handler_Prototype(PlugIn):
	name = "examplecommand"
	count = 0
	description = "an example command"
	discofeatures = [NS_COMMANDS, NS_DATA]

	def __init__(self, jid=""):
		PlugIn.__init__(self)
		DBG_LINE = "command"
		self.sessioncount = 0
		self.sessions = {}
		self.discoinfo = {"ids": [{"category": "automation", "type": "command-node", "name": self.description}], "features": self.discofeatures}
		self._jid = jid

	def plugin(self, owner):
		self._commands = owner
		self._owner = owner._owner
		self._commands.addCommand(self.name, self._DiscoHandler, self.Execute, jid=self._jid)

	def plugout(self):
		self._commands.delCommand(self.name, self._jid)

	def getSessionID(self):
		self.count += 1
		return "cmd-%s-%d" % (self.name, self.count)

	def Execute(self, conn, request):
		try:
			session = request.getTagAttr("command", "sessionid")
		except Exception:
			session = None
		try:
			action = request.getTagAttr("command", "action")
		except Exception:
			action = None
		if action == None:
			action = "execute"
		if session in self.sessions:
			if self.sessions[session]["jid"] == request.getFrom():
				if action in self.sessions[session]["actions"]:
					self.sessions[session]["actions"][action](conn, request)
				else:
					self._owner.send(Error(request, ERR_BAD_REQUEST))
					raise NodeProcessed()
			else:
				self._owner.send(Error(request, ERR_BAD_REQUEST))
				raise NodeProcessed()
		elif session != None:
			self._owner.send(Error(request, ERR_BAD_REQUEST))
			raise NodeProcessed()
		else:
			self.initial[action](conn, request)

	def _DiscoHandler(self, conn, request, typ):
		if typ == "list":
			result = (request.getTo(), self.name, self.description)
		elif typ == "items":
			result = []
		elif typ == "info":
			result = self.discoinfo
		return result

class TestCommand(Command_Handler_Prototype):
	name = "testcommand"
	description = "a noddy example command"

	def __init__(self, jid=""):
		Command_Handler_Prototype.__init__(self, jid)
		self.initial = {"execute": self.cmdFirstStage}

	def cmdFirstStage(self, conn, request):
		try:
			session = request.getTagAttr("command", "sessionid")
		except Exception:
			session = None
		if session == None:
			session = self.getSessionID()
			self.sessions[session] = {"jid": request.getFrom(), "actions": {"cancel": self.cmdCancel, "next": self.cmdSecondStage, "execute": self.cmdSecondStage}, "data": {"type": None}}
		reply = request.buildReply("result")
		form = DataForm(title="Select type of operation", data=["Use the combobox to select the type of calculation you would like to do, then click Next.", DataField(name="calctype", desc="Calculation Type", value=self.sessions[session]["data"]["type"], options=[["circlediameter", "Calculate the Diameter of a circle"], ["circlearea", "Calculate the area of a circle"]], typ="list-single", required=1)])
		replypayload = [Node("actions", attrs={"execute": "next"}, payload=[Node("next")]), form]
		reply.addChild(name="command", namespace=NS_COMMANDS, attrs={"node": request.getTagAttr("command", "node"), "sessionid": session, "status": "executing"}, payload=replypayload)
		self._owner.send(reply)
		raise NodeProcessed()

	def cmdSecondStage(self, conn, request):
		form = DataForm(node=request.getTag(name="command").getTag(name="x", namespace=NS_DATA))
		self.sessions[request.getTagAttr("command", "sessionid")]["data"]["type"] = form.getField("calctype").getValue()
		self.sessions[request.getTagAttr("command", "sessionid")]["actions"] = {"cancel": self.cmdCancel, None: self.cmdThirdStage, "previous": self.cmdFirstStage, "execute": self.cmdThirdStage, "next": self.cmdThirdStage}
		self.cmdSecondStageReply(conn, request)

	def cmdSecondStageReply(self, conn, request):
		reply = request.buildReply("result")
		form = DataForm(title="Enter the radius", data=["Enter the radius of the circle (numbers only)", DataField(desc="Radius", name="radius", typ="text-single")])
		replypayload = [Node("actions", attrs={"execute": "complete"}, payload=[Node("complete"), Node("prev")]), form]
		reply.addChild(name="command", namespace=NS_COMMANDS, attrs={"node": request.getTagAttr("command", "node"), "sessionid": request.getTagAttr("command", "sessionid"), "status": "executing"}, payload=replypayload)
		self._owner.send(reply)
		raise NodeProcessed()

	def cmdThirdStage(self, conn, request):
		form = DataForm(node=request.getTag(name="command").getTag(name="x", namespace=NS_DATA))
		try:
			numb = float(form.getField("radius").getValue())
		except Exception:
			self.cmdSecondStageReply(conn, request)
		from math import pi
		if self.sessions[request.getTagAttr("command", "sessionid")]["data"]["type"] == "circlearea":
			result = (numb ** 2) * pi
		else:
			result = numb * 2 * pi
		reply = request.buildReply("result")
		form = DataForm(typ="result", data=[DataField(desc="result", name="result", value=result)])
		reply.addChild(name="command", namespace=NS_COMMANDS, attrs={"node": request.getTagAttr("command", "node"), "sessionid": request.getTagAttr("command", "sessionid"), "status": "completed"}, payload=[form])
		self._owner.send(reply)
		raise NodeProcessed()

	def cmdCancel(self, conn, request):
		reply = request.buildReply("result")
		reply.addChild(name="command", namespace=NS_COMMANDS, attrs={"node": request.getTagAttr("command", "node"), "sessionid": request.getTagAttr("command", "sessionid"), "status": "cancelled"})
		self._owner.send(reply)
		del self.sessions[request.getTagAttr("command", "sessionid")]
