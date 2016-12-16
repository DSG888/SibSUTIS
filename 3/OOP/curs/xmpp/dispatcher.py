import sys
import time
from . import simplexml

from .plugin import PlugIn
from .protocol import *
from select import select
from xml.parsers.expat import ExpatError

DefaultTimeout = 25
ID = 0

DBG_LINE = "dispatcher"

if sys.hexversion >= 0x30000F0:

	def deferredRaise(e):
		raise e[0](e[1]).with_traceback(e[2])

else:

	def deferredRaise(e):
		raise e[0], e[1], e[2]

class Dispatcher(PlugIn):
	def __init__(self):
		PlugIn.__init__(self)
		self.handlers = {}
		self._expected = {}
		self.dc=False
		self._defaultHandler = None
		self._pendingExceptions = []
		self._eventHandler = None
		self._cycleHandlers = []
		self._exported_methods = [self.Process, self.RegisterHandler, self.RegisterEventHandler, self.UnregisterCycleHandler, self.RegisterCycleHandler, self.RegisterHandlerOnce, self.UnregisterHandler, self.RegisterProtocol, self.WaitForResponse, self.SendAndWaitForResponse, self.send, self.SendAndCallForResponse, self.disconnect, self.iter]

	def dumpHandlers(self):
		return self.handlers

	def restoreHandlers(self, handlers):
		self.handlers = handlers

	def _init(self):
		self.RegisterNamespace("unknown")
		self.RegisterNamespace(NS_STREAMS)
		self.RegisterNamespace(self._owner.defaultNamespace)
		self.RegisterProtocol("iq", Iq)
		self.RegisterProtocol("presence", Presence)
		self.RegisterProtocol("message", Message)
		self.RegisterHandler("error", self.streamErrorHandler, xmlns=NS_STREAMS)

	def plugin(self, owner):
		self._init()
		for method in self._old_owners_methods:
			if method.__name__ == "send":
				self._owner_send = method
				break
		self._owner.lastErrNode = None
		self._owner.lastErr = None
		self._owner.lastErrCode = None
		self.StreamInit()

	def plugout(self):
		self.Stream.dispatch = None
		self.Stream.DEBUG = None
		self.Stream.features = None
		self.Stream.destroy()

	def StreamInit(self):
		self.Stream = simplexml.NodeBuilder()
		self.Stream._dispatch_depth = 2
		self.Stream.dispatch = self.dispatch
		self.Stream.stream_header_received = self._check_stream_start
		self._owner.debug_flags.append(simplexml.DBG_NODEBUILDER)
		self.Stream.DEBUG = self._owner.DEBUG
		self.Stream.features = None
		self._metastream = Node("stream:stream")
		self._metastream.setNamespace(self._owner.Namespace)
		self._metastream.setAttr("version", "1.0")
		self._metastream.setAttr("xmlns:stream", NS_STREAMS)
		self._metastream.setAttr("to", self._owner.Server)
		self._owner.send("<?xml version=\"1.0\"?>%s>" % str(self._metastream)[:-2])

	def _check_stream_start(self, ns, tag, attrs):
		if ns != NS_STREAMS or tag != "stream":
			raise ValueError("Incorrect stream start: (%s,%s). Terminating." % (tag, ns))

	def Process(self, timeout=8):
		for handler in self._cycleHandlers:
			handler(self)
		if self._pendingExceptions:
			deferredRaise(self._pendingExceptions.pop())
		if self._owner.Connection.pending_data(timeout):
			try:
				data = self._owner.Connection.receive()
			except IOError:
				return None
			try:
				self.Stream.Parse(data)
			except ExpatError:
				pass
			if self._pendingExceptions:
				deferredRaise(self._pendingExceptions.pop())
			if data:
				return len(data)
		return "0"

	def RegisterNamespace(self, xmlns, order="info"):
		self.DEBUG("Registering namespace \"%s\"" % xmlns, order)
		self.handlers[xmlns] = {}
		self.RegisterProtocol("unknown", Protocol, xmlns=xmlns)
		self.RegisterProtocol("default", Protocol, xmlns=xmlns)

	def RegisterProtocol(self, tag_name, Proto, xmlns=None, order="info"):
		if not xmlns:
			xmlns = self._owner.defaultNamespace
		self.DEBUG("Registering protocol \"%s\" as %s(%s)" % (tag_name, Proto, xmlns), order)
		self.handlers[xmlns][tag_name] = {"type": Proto, "default": []}

	def RegisterNamespaceHandler(self, xmlns, handler, typ="", ns="", makefirst=0, system=0):
		self.RegisterHandler("default", handler, typ, ns, xmlns, makefirst, system)

	def RegisterHandler(self, name, handler, typ="", ns="", xmlns=None, makefirst=0, system=0):
		if not xmlns:
			xmlns = self._owner.defaultNamespace
		self.DEBUG("Registering handler %s for \"%s\" type->%s ns->%s(%s)" % (handler, name, typ, ns, xmlns), "info")
		if not typ and not ns:
			typ = "default"
		if xmlns not in self.handlers:
			self.RegisterNamespace(xmlns, "warn")
		if name not in self.handlers[xmlns]:
			self.RegisterProtocol(name, Protocol, xmlns, "warn")
		if typ + ns not in self.handlers[xmlns][name]:
			self.handlers[xmlns][name][typ + ns] = []
		if makefirst:
			self.handlers[xmlns][name][typ + ns].insert(0, {"func": handler, "system": system})
		else:
			self.handlers[xmlns][name][typ + ns].append({"func": handler, "system": system})

	def RegisterHandlerOnce(self, name, handler, typ="", ns="", xmlns=None, makefirst=0, system=0):
		if not xmlns:
			xmlns = self._owner.defaultNamespace
		self.RegisterHandler(name, handler, typ, ns, xmlns, makefirst, system)

	def UnregisterHandler(self, name, handler, typ="", ns="", xmlns=None):
		if not xmlns:
			xmlns = self._owner.defaultNamespace
		if xmlns not in self.handlers:
			return None
		if not typ and not ns:
			typ = "default"
		for pack in self.handlers[xmlns][name][typ + ns]:
			if handler == pack["func"]:
				break
		else:
			pack = None
		try:
			self.handlers[xmlns][name][typ + ns].remove(pack)
		except ValueError:
			pass

	def RegisterDefaultHandler(self, handler):
		self._defaultHandler = handler

	def RegisterEventHandler(self, handler):
		self._eventHandler = handler

	def returnStanzaHandler(self, conn, stanza):
		if stanza.getType() in ("get", "set"):
			conn.send(Error(stanza, ERR_FEATURE_NOT_IMPLEMENTED))

	def streamErrorHandler(self, conn, error):
		name, text = "error", error.getData()
		for tag in error.getChildren():
			if tag.getNamespace() == NS_XMPP_STREAMS:
				if tag.getName() == "text":
					text = tag.getData()
				else:
					name = tag.getName()
		if name in stream_exceptions.keys():
			exc = stream_exceptions[name]
		else:
			exc = StreamError
		raise exc((name, text))

	def RegisterCycleHandler(self, handler):
		if handler not in self._cycleHandlers:
			self._cycleHandlers.append(handler)

	def UnregisterCycleHandler(self, handler):
		if handler in self._cycleHandlers:
			self._cycleHandlers.remove(handler)

	def Event(self, realm, event, data):
		if self._eventHandler:
			self._eventHandler(realm, event, data)

	def dispatch(self, stanza, session=None, direct=0):
		if not session:
			session = self
		session.Stream._mini_dom = None
		name = stanza.getName()
		if not direct and self._owner._route:
			if name == "route":
				if stanza.getAttr("error") == None:
					if len(stanza.getChildren()) == 1:
						stanza = stanza.getChildren()[0]
						name = stanza.getName()
					else:
						for each in stanza.getChildren():
							self.dispatch(each, session, direct=1)
						return None
			elif name == "presence":
				return None
			elif name in ("features", "bind"):
				pass
			else:
				raise UnsupportedStanzaType(name)
		if name == "features":
			session.Stream.features = stanza
		xmlns = stanza.getNamespace()
		if xmlns not in self.handlers:
			self.DEBUG("Unknown namespace: " + xmlns, "warn")
			xmlns = "unknown"
		if name not in self.handlers[xmlns]:
			self.DEBUG("Unknown stanza: " + name, "warn")
			name = "unknown"
		else:
			self.DEBUG("Got %s/%s stanza" % (xmlns, name), "ok")
		if isinstance(stanza, Node):
			stanza = self.handlers[xmlns][name]["type"](node=stanza)
		typ = stanza.getType()
		if not typ:
			typ = ""
		stanza.props = stanza.getProperties()
		ID = stanza.getID()
		session.DEBUG("Dispatching %s stanza with type->%s props->%s id->%s" % (name, typ, stanza.props, ID), "ok")
		ls = ["default"] # we will use all handlers:
		if typ in self.handlers[xmlns][name]:
			ls.append(typ) # from very common...
		for prop in stanza.props:
			if prop in self.handlers[xmlns][name]:
				ls.append(prop)
			if typ and (typ + prop) in self.handlers[xmlns][name]:
				ls.append(typ + prop) # ...to very particular
		chain = self.handlers[xmlns]["default"]["default"]
		for key in ls:
			if key:
				chain = chain + self.handlers[xmlns][name][key]
		output = ""
		if ID in session._expected:
			user = 0
			if isinstance(session._expected[ID], tuple):
				cb, args = session._expected.pop(ID)
				session.DEBUG("Expected stanza arrived. Callback %s(%s) found!" % (cb, args), "ok")
				try:
					cb(session, stanza, **args)
				except NodeProcessed:
					pass
			else:
				session.DEBUG("Expected stanza arrived!", "ok")
				session._expected[ID] = stanza
		else:
			user = 1
		for handler in chain:
			if user or handler["system"]:
				try:
					handler["func"](session, stanza)
				except NodeProcessed:
					user = 0
				except Exception:
					self._pendingExceptions.insert(0, sys.exc_info())
		if user and self._defaultHandler:
			self._defaultHandler(session, stanza)

	def WaitForResponse(self, ID, timeout=DefaultTimeout):
		self._expected[ID] = None
		abort_time = time.time() + timeout
		self.DEBUG("Waiting for ID:%s with timeout %s..." % (ID, timeout), "wait")
		while not self._expected[ID]:
			if not self.Process(0.04):
				self._owner.lastErr = "Disconnect"
				return None
			if time.time() > abort_time:
				self._owner.lastErr = "Timeout"
				return None
		resp = self._expected.pop(ID)
		if resp.getErrorCode():
			self._owner.lastErrNode = resp
			self._owner.lastErr = resp.getError()
			self._owner.lastErrCode = resp.getErrorCode()
		return resp

	def SendAndWaitForResponse(self, stanza, timeout=DefaultTimeout):
		return self.WaitForResponse(self.send(stanza), timeout)

	def SendAndCallForResponse(self, stanza, func, args={}):
		self._expected[self.send(stanza)] = (func, args)

	def send(self, stanza):
		if isinstance(stanza, basestring):
			return self._owner_send(stanza)
		if not isinstance(stanza, Protocol):
			id = None
		elif not stanza.getID():
			global ID
			ID += 1
			id = repr(ID)
			stanza.setID(id)
		else:
			id = stanza.getID()
		if self._owner._registered_name and not stanza.getAttr("from"):
			stanza.setAttr("from", self._owner._registered_name)
		if self._owner._route and stanza.getName() != "bind":
			to = self._owner.Server
			if stanza.getTo() and stanza.getTo().getDomain():
				to = stanza.getTo().getDomain()
			frm = stanza.getFrom()
			if frm.getDomain():
				frm = frm.getDomain()
			route = Protocol("route", to=to, frm=frm, payload=[stanza])
			stanza = route
		stanza.setNamespace(self._owner.Namespace)
		stanza.setParent(self._metastream)
		self._owner_send(stanza)
		return id

	def disconnect(self):
		if self._owner.connected:
			self._owner_send("</stream:stream>")
			while self.Process(1):
				pass

	iter = type(send)(Process.__code__, Process.__globals__, name = "iter", argdefs = Process.__defaults__, closure = Process.__closure__)
