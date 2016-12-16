from .dispatcher import *
from .plugin import PlugIn

class Browser(PlugIn):
	def __init__(self):
		PlugIn.__init__(self)
		DBG_LINE = "browser"
		self._exported_methods = []
		self._handlers = {"": {}}

	def plugin(self, owner):
		owner.RegisterHandler("iq", self._DiscoveryHandler, typ="get", ns=NS_DISCO_INFO)
		owner.RegisterHandler("iq", self._DiscoveryHandler, typ="get", ns=NS_DISCO_ITEMS)

	def plugout(self):
		self._owner.UnregisterHandler("iq", self._DiscoveryHandler, typ="get", ns=NS_DISCO_INFO)
		self._owner.UnregisterHandler("iq", self._DiscoveryHandler, typ="get", ns=NS_DISCO_ITEMS)

	def _traversePath(self, node, jid, set=0):
		if jid in self._handlers:
			cur = self._handlers[jid]
		elif set:
			self._handlers[jid] = {}
			cur = self._handlers[jid]
		else:
			cur = self._handlers[""]
		if node is None:
			node = [None]
		else:
			node = node.replace("/", " /").split("/")
		for i in node:
			if i != "" and i in cur:
				cur = cur[i]
			elif set and i != "":
				cur[i] = {dict: cur, str: i}
				cur = cur[i]
			elif set or "" in cur:
				return cur, ""
			else:
				return None, None
		if 1 in cur or set:
			return cur, 1
		raise Exception("Corrupted data")

	def setDiscoHandler(self, handler, node="", jid=""):
		self.DEBUG("Registering handler %s for \"%s\" node->%s" % (handler, jid, node), "info")
		node, key = self._traversePath(node, jid, 1)
		node[key] = handler

	def getDiscoHandler(self, node="", jid=""):
		node, key = self._traversePath(node, jid)
		if node:
			return node[key]

	def delDiscoHandler(self, node="", jid=""):
		node, key = self._traversePath(node, jid)
		if node:
			handler = node[key]
			del node[dict][node[str]]
			return handler

	def _DiscoveryHandler(self, conn, request):
		node = request.getQuerynode()
		if node:
			nodestr = node
		else:
			nodestr = "None"
		handler = self.getDiscoHandler(node, request.getTo())
		if not handler:
			self.DEBUG("No Handler for request with jid->%s node->%s ns->%s" % (request.getTo().__str__().encode("utf8"), nodestr.encode("utf8"), request.getQueryNS().encode("utf8")), "error")
			conn.send(Error(request, ERR_ITEM_NOT_FOUND))
			raise NodeProcessed()
		self.DEBUG("Handling request with jid->%s node->%s ns->%s" % (request.getTo().__str__().encode("utf8"), nodestr.encode("utf8"), request.getQueryNS().encode("utf8")), "ok")
		rep = request.buildReply("result")
		if node:
			rep.setQuerynode(node)
		q = rep.getTag("query")
		if request.getQueryNS() == NS_DISCO_ITEMS:
			if isinstance(handler, dict):
				lst = handler["items"]
			else:
				lst = handler(conn, request, "items")
			if lst == None:
				conn.send(Error(request, ERR_ITEM_NOT_FOUND))
				raise NodeProcessed()
			for item in lst:
				q.addChild("item", item)
		elif request.getQueryNS() == NS_DISCO_INFO:
			if isinstance(handler, dict):
				dt = handler["info"]
			else:
				dt = handler(conn, request, "info")
			if dt == None:
				conn.send(Error(request, ERR_ITEM_NOT_FOUND))
				raise NodeProcessed()
			for id in dt["ids"]:
				q.addChild("identity", id)
			for feature in dt["features"]:
				q.addChild("feature", {"var": feature})
			if "xdata" in dt:
				q.addChild(node=dt["xdata"])
		conn.send(rep)
		raise NodeProcessed()
