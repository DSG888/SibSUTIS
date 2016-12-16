from . import debug
from . import transports
from . import dispatcher
from . import auth
from . import roster

from .plugin import PlugIn

Debug = debug
Debug.DEBUGGING_IS_ON = 1

Debug.Debug.colors["socket"] = debug.color_dark_gray
Debug.Debug.colors["CONNECTproxy"] = debug.color_dark_gray
Debug.Debug.colors["nodebuilder"] = debug.color_brown
Debug.Debug.colors["client"] = debug.color_cyan
Debug.Debug.colors["component"] = debug.color_cyan
Debug.Debug.colors["dispatcher"] = debug.color_green
Debug.Debug.colors["browser"] = debug.color_blue
Debug.Debug.colors["auth"] = debug.color_yellow
Debug.Debug.colors["roster"] = debug.color_magenta
Debug.Debug.colors["ibb"] = debug.color_yellow
Debug.Debug.colors["down"] = debug.color_brown
Debug.Debug.colors["up"] = debug.color_brown
Debug.Debug.colors["data"] = debug.color_brown
Debug.Debug.colors["ok"] = debug.color_green
Debug.Debug.colors["warn"] = debug.color_yellow
Debug.Debug.colors["error"] = debug.color_red
Debug.Debug.colors["start"] = debug.color_dark_gray
Debug.Debug.colors["stop"] = debug.color_dark_gray
Debug.Debug.colors["sent"] = debug.color_yellow
Debug.Debug.colors["got"] = debug.color_bright_cyan

DBG_CLIENT = "client"
DBG_COMPONENT = "component"


class CommonClient:
	def __init__(self, server, port=5222, debug=["always", "nodebuilder"]):
		if isinstance(self, Client):
			self.Namespace, self.DBG = "jabber:client", DBG_CLIENT
		elif isinstance(self, Component):
			self.Namespace, self.DBG = dispatcher.NS_COMPONENT_ACCEPT, DBG_COMPONENT
		self.defaultNamespace = self.Namespace
		self.disconnect_handlers = []
		self.Server = server
		self.Port = port
		if debug and not isinstance(debug, list):
			debug = ["always", "nodebuilder"]
		self._DEBUG = Debug.Debug(debug)
		self.DEBUG = self._DEBUG.Show
		self.debug_flags = self._DEBUG.debug_flags
		self.debug_flags.append(self.DBG)
		self._owner = self
		self._registered_name = None
		self.RegisterDisconnectHandler(self.DisconnectHandler)
		self.connected = ""
		self._route = 0

	def RegisterDisconnectHandler(self, handler):
		self.disconnect_handlers.append(handler)

	def UnregisterDisconnectHandler(self, handler):
		self.disconnect_handlers.remove(handler)

	def disconnected(self):
		self.connected = ""
		self.DEBUG(self.DBG, "Disconnect detected", "stop")
		self.disconnect_handlers.reverse()
		for dhnd in self.disconnect_handlers:
			dhnd()
		self.disconnect_handlers.reverse()
		if hasattr(self, "TLS"):
			self.TLS.PlugOut()

	def DisconnectHandler(self):
		raise IOError("Disconnected!")

	def event(self, eventName, args={}):
		print("Event: %s-%s" % (eventName, args))

	def isConnected(self):
		return self.connected

	def reconnectAndReauth(self, handlerssave=None):
		Dispatcher_ = False
		if not handlerssave:
			Dispatcher_, handlerssave = True, self.Dispatcher.dumpHandlers()
		if hasattr(self, "ComponentBind"):
			self.ComponentBind.PlugOut()
		if hasattr(self, "Bind"):
			self.Bind.PlugOut()
		self._route = 0
		if hasattr(self, "NonSASL"):
			self.NonSASL.PlugOut()
		if hasattr(self, "SASL"):
			self.SASL.PlugOut()
		if hasattr(self, "TLS"):
			self.TLS.PlugOut()
		if Dispatcher_:
			self.Dispatcher.PlugOut()
		if hasattr(self, "HTTPPROXYsocket"):
			self.HTTPPROXYsocket.PlugOut()
		if hasattr(self, "TCPsocket"):
			self.TCPsocket.PlugOut()
		if not self.connect(server=self._Server, proxy=self._Proxy):
			return None
		if not self.auth(self._User, self._Password, self._Resource):
			return None
		self.Dispatcher.restoreHandlers(handlerssave)
		return self.connected

	def connect(self, server=None, proxy=None, ssl=None, use_srv=False):
		if not server:
			server = (self.Server, self.Port)
		if proxy:
			sock = transports.HTTPPROXYsocket(proxy, server, use_srv)
		else:
			sock = transports.TCPsocket(server, use_srv)
		connected = sock.PlugIn(self)
		if not connected:
			sock.PlugOut()
			return None
		self._Server, self._Proxy = server, proxy
		self.connected = "tcp"
		if (ssl is None and self.Connection.getPort() in (5223, 443)) or ssl:
			try:
				transports.TLS().PlugIn(self, now=1)
				self.connected = "ssl"
			except transports.socket.sslerror:
				return None
		dispatcher.Dispatcher().PlugIn(self)
		while self.Dispatcher.Stream._document_attrs is None:
			if not self.Process(1):
				return None
		if "version" in self.Dispatcher.Stream._document_attrs and self.Dispatcher.Stream._document_attrs["version"] == "1.0":
			while not self.Dispatcher.Stream.features and self.Process(1):
				pass
		return self.connected

class Client(CommonClient):
	def connect(self, server=None, proxy=None, secure=None, use_srv=True):
		if not CommonClient.connect(self, server, proxy, secure, use_srv) or secure != None and not secure:
			return self.connected
		transports.TLS().PlugIn(self)
		if not hasattr(self, "Dispatcher"):
			return None
		if "version" not in self.Dispatcher.Stream._document_attrs or not self.Dispatcher.Stream._document_attrs["version"] == "1.0":
			return self.connected
		while not self.Dispatcher.Stream.features and self.Process(1):
			pass
		if not self.Dispatcher.Stream.features.getTag("starttls"):
			return self.connected
		while not self.TLS.starttls and self.Process(1):
			pass
		if not hasattr(self, "TLS") or self.TLS.starttls != "success":
			self.event("tls_failed")
			return self.connected
		self.connected = "tls"
		return self.connected

	def auth(self, user, password, resource="", sasl=1):
		self._User, self._Password, self._Resource = user, password, resource
		while not self.Dispatcher.Stream._document_attrs and self.Process(1):
			pass
		if "version" in self.Dispatcher.Stream._document_attrs and self.Dispatcher.Stream._document_attrs["version"] == "1.0":
			while not self.Dispatcher.Stream.features and self.Process(1):
				pass
		if sasl:
			auth.SASL(user, password).PlugIn(self)
		if not sasl or self.SASL.startsasl == "not-supported":
			if not resource:
				resource = "xmpppy"
			if auth.NonSASL(user, password, resource).PlugIn(self):
				self.connected += "+old_auth"
				return "old_auth"
			return None
		self.SASL.auth()
		while self.SASL.startsasl == "in-process" and self.Process(1):
			pass
		if self.SASL.startsasl == "success":
			auth.Bind().PlugIn(self)
			while self.Bind.bound is None and self.Process(1):
				pass
			if self.Bind.Bind(resource):
				self.connected += "+sasl"
				return "sasl"
		elif hasattr(self, "SASL"):
			self.SASL.PlugOut()

	def getRoster(self):
		if not hasattr(self, "Roster"):
			roster.Roster().PlugIn(self)
		return self.Roster.getRoster()

	def sendInitPresence(self, requestRoster=1):
		self.sendPresence(requestRoster=requestRoster)

	def sendPresence(self, jid=None, typ=None, requestRoster=0):
		if requestRoster:
			roster.Roster().PlugIn(self)
		self.send(dispatcher.Presence(to=jid, typ=typ))

class Component(CommonClient):
	def __init__(self, transport, port=5347, typ=None, debug=["always", "nodebuilder"], domains=None, sasl=0, bind=0, route=0, xcp=0):
		CommonClient.__init__(self, transport, port=port, debug=debug)
		self.typ = typ
		self.sasl = sasl
		self.bind = bind
		self.route = route
		self.xcp = xcp
		if domains:
			self.domains = domains
		else:
			self.domains = [transport]

	def connect(self, server=None, proxy=None):
		if self.sasl:
			self.Namespace = auth.NS_COMPONENT_1
			self.Server = server[0]
		CommonClient.connect(self, server=server, proxy=proxy)
		if self.connected and (self.typ == "jabberd2" or not self.typ and self.Dispatcher.Stream.features != None) and (not self.xcp):
			self.defaultNamespace = auth.NS_CLIENT
			self.Dispatcher.RegisterNamespace(self.defaultNamespace)
			self.Dispatcher.RegisterProtocol("iq", dispatcher.Iq)
			self.Dispatcher.RegisterProtocol("message", dispatcher.Message)
			self.Dispatcher.RegisterProtocol("presence", dispatcher.Presence)
		return self.connected

	def dobind(self, sasl):
		self._route = self.route
		if self.bind:
			for domain in self.domains:
				auth.ComponentBind(sasl).PlugIn(self)
				while self.ComponentBind.bound is None:
					self.Process(1)
				if (not self.ComponentBind.Bind(domain)):
					self.ComponentBind.PlugOut()
					return None
				self.ComponentBind.PlugOut()

	def auth(self, name, password, dup=None):
		self._User, self._Password, self._Resource = name, password, ""
		try:
			if self.sasl:
				auth.SASL(name, password).PlugIn(self)
			if not self.sasl or self.SASL.startsasl == "not-supported":
				if auth.NonSASL(name, password, "").PlugIn(self):
					self.dobind(sasl=False)
					self.connected += "+old_auth"
					return "old_auth"
				return None
			self.SASL.auth()
			while self.SASL.startsasl == "in-process" and self.Process(1):
				pass
			if self.SASL.startsasl == "success":
				self.dobind(sasl=True)
				self.connected += "+sasl"
				return "sasl"
			else:
				raise auth.NotAuthorized(self.SASL.startsasl)
		except Exception:
			self.DEBUG(self.DBG, "Failed to authenticate %s" % name, "error")
