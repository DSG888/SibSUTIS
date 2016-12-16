from .plugin import PlugIn
from .protocol import *

class Roster(PlugIn):
	def __init__(self):
		PlugIn.__init__(self)
		self.DBG_LINE = "roster"
		self._data = {}
		self.set = None
		self._exported_methods = [self.getRoster]

	def plugin(self, owner, request=1):
		self._owner.RegisterHandler("iq", self.RosterIqHandler, "result", NS_ROSTER)
		self._owner.RegisterHandler("iq", self.RosterIqHandler, "set", NS_ROSTER)
		self._owner.RegisterHandler("presence", self.PresenceHandler)
		if request:
			self.Request()

	def Request(self, force=0):
		if self.set is None:
			self.set = 0
		elif not force:
			return None
		self._owner.send(Iq("get", NS_ROSTER))
		self.DEBUG("Roster requested from server", "start")

	def getRoster(self):
		if not self.set:
			self.Request()
		while not self.set:
			self._owner.Process(10)
		return self

	def RosterIqHandler(self, dis, stanza):
		for item in stanza.getTag("query").getTags("item"):
			jid = item.getAttr("jid")
			if item.getAttr("subscription") == "remove":
				if jid in self._data:
					del self._data[jid]
				raise NodeProcessed() # a MUST
			self.DEBUG("Setting roster item %s..." % jid, "ok")
			if jid not in self._data:
				self._data[jid] = {}
			self._data[jid]["name"] = item.getAttr("name")
			self._data[jid]["ask"] = item.getAttr("ask")
			self._data[jid]["subscription"] = item.getAttr("subscription")
			self._data[jid]["groups"] = []
			if "resources" not in self._data[jid]:
				self._data[jid]["resources"] = {}
			for group in item.getTags("group"):
				self._data[jid]["groups"].append(group.getData())
		self._data["@".join((self._owner.User, self._owner.Server))] = {"resources": {}, "name": None, "ask": None, "subscription": None, "groups": None, }
		self.set = 1
		raise NodeProcessed() # a MUST. Otherwise you'll get back an <iq type='error'/>

	def PresenceHandler(self, dis, pres):
		jid = JID(pres.getFrom())
		if jid.getStripped() not in self._data:
			self._data[jid.getStripped()] = {"name": None, "ask": None, "subscription": "none", "groups": ["Not in roster"], "resources": {}}
		item = self._data[jid.getStripped()]
		typ = pres.getType()
		if not typ:
			self.DEBUG("Setting roster item %s for resource %s..." % (jid.getStripped(), jid.getResource()), "ok")
			item["resources"][jid.getResource()] = res = {"show": None, "status": None, "priority": "0", "timestamp": None}
			if pres.getTag("show"):
				res["show"] = pres.getShow()
			if pres.getTag("status"):
				res["status"] = pres.getStatus()
			if pres.getTag("priority"):
				res["priority"] = pres.getPriority()
			if not pres.getTimestamp():
				pres.setTimestamp()
			res["timestamp"] = pres.getTimestamp()
		elif typ == "unavailable" and jid.getResource() in item["resources"]:
			del item["resources"][jid.getResource()]
		# Need to handle type="error" also

	def _getItemData(self, jid, dataname):
		jid = jid[:(jid + "/").find("/")]
		return self._data[jid][dataname]

	def _getResourceData(self, jid, dataname):
		if jid.find("/") + 1:
			jid, resource = jid.split("/", 1)
			if resource in self._data[jid]["resources"]:
				return self._data[jid]["resources"][resource][dataname]
		elif self._data[jid]["resources"].keys():
			lastpri = -129
			for r in self._data[jid]["resources"].keys():
				if int(self._data[jid]["resources"][r]["priority"]) > lastpri:
					resource, lastpri = r, int(self._data[jid]["resources"][r]["priority"])
			return self._data[jid]["resources"][resource][dataname]

	def delItem(self, jid):
		self._owner.send(Iq("set", NS_ROSTER, payload=[Node("item", {"jid": jid, "subscription": "remove"})]))

	def getAsk(self, jid):
		return self._getItemData(jid, "ask")

	def getGroups(self, jid):
		return self._getItemData(jid, "groups")

	def getName(self, jid):
		return self._getItemData(jid, "name")

	def getPriority(self, jid):
		return self._getResourceData(jid, "priority")

	def getRawRoster(self):
		return self._data

	def getRawItem(self, jid):
		return self._data[jid[:(jid + "/").find("/")]]

	def getShow(self, jid):
		return self._getResourceData(jid, "show")

	def getStatus(self, jid):
		return self._getResourceData(jid, "status")

	def getSubscription(self, jid):
		return self._getItemData(jid, "subscription")

	def getResources(self, jid):
		return self._data[jid[:(jid + "/").find("/")]]["resources"].keys()

	def setItem(self, jid, name=None, groups=[]):
		iq = Iq("set", NS_ROSTER)
		query = iq.getTag("query")
		attrs = {"jid": jid}
		if name:
			attrs["name"] = name
		item = query.setTag("item", attrs)
		for group in groups:
			item.addChild(node=Node("group", payload=[group]))
		self._owner.send(iq)

	def getItems(self):
		return self._data.keys()

	def keys(self):
		return self._data.keys()

	def __getitem__(self, item):
		return self._data[item]

	def getItem(self, item):
		if item in self._data:
			return self._data[item]

	def Subscribe(self, jid):
		self._owner.send(Presence(jid, "subscribe"))

	def Unsubscribe(self, jid):
		self._owner.send(Presence(jid, "unsubscribe"))

	def Authorize(self, jid):
		self._owner.send(Presence(jid, "subscribed"))

	def Unauthorize(self, jid):
		self._owner.send(Presence(jid, "unsubscribed"))
