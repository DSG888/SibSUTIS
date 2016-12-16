import sys
import socket
if sys.hexversion >= 0x20600F0:
	import ssl
import thread
import time
from . import dispatcher

from base64 import encodestring
from select import select
from .simplexml import ustr
from .plugin import PlugIn
from .protocol import *

# http://pydns.sourceforge.net
try:
	import dns
except ImportError:
	dns = None

DATA_RECEIVED = 'DATA RECEIVED'
DATA_SENT = 'DATA SENT'
DBG_CONNECT_PROXY = 'CONNECTproxy'

BUFLEN = 2024
SEND_INTERVAL = 0

class SendSemaphore(object):

	def __init__(self):
		self.__lock = thread.allocate_lock()
		self.__released = 0
		self.interval = SEND_INTERVAL

	def set_send_interval(self, interval):
		self.interval = interval

	def acquire(self, blocking=1):
		rc = self.__lock.acquire(blocking)
		if blocking and self.interval:
			elapsed = time.time() - self.__released
			if elapsed < self.interval:
				time.sleep(self.interval - elapsed)
		return rc

	__enter__ = acquire

	def release(self):
		self.__released = time.time()
		self.__lock.release()

	def __exit__(self, *args):
		self.release()

class error:
	"""
	An exception to be raised in case of low-level errors in methods of 'transports' module.
	"""
	def __init__(self, comment):
		"""
		Cache the descriptive string.
		"""
		self._comment = comment

	def __str__(self):
		"""
		Serialize exception into pre-cached descriptive string.
		"""
		return self._comment

class TCPsocket(PlugIn):
	def __init__(self, server=None, use_srv=True):
		PlugIn.__init__(self)
		self.DBG_LINE = "socket"
		self._sequence = SendSemaphore()
		self.set_send_interval = self._sequence.set_send_interval
		self._exported_methods = [self.send, self.disconnect, self.set_send_interval]
		self._server, self.use_srv = server, use_srv

	def srv_lookup(self, server):
		if dns:
			query = "_xmpp-client._tcp.%s" % server[0]
			try:
				dns.DiscoverNameServers()
				dns__ = dns.Request()
				response = dns__.req(query, qtype="SRV")
				if response.answers:
					# Sort by priority, according to RFC 2782.
					answers = sorted(response.answers, key=lambda a: a["data"][0])
					(port, host) = answers[0]["data"][2:]
					server = str(host), int(port)
			except dns.DNSError:
				self.DEBUG("An error occurred while looking up %s." % query, "warn")
		return server

	def plugin(self, owner):
		if not self._server:
			self._server = (self._owner.Server, 5222)
		if self.use_srv:
			server = self.srv_lookup(self._server)
		else:
			server = self._server
		if not self.connect(server):
			return None
		self._owner.Connection = self
		self._owner.RegisterDisconnectHandler(self.disconnected)
		return "ok"

	def getHost(self):
		return self._server[0]

	def getPort(self):
		return self._server[1]

	def connect(self, server=None):
		if not server:
			server = self._server
		host, port = server
		socktype = socket.SOCK_STREAM
		try:
			lookup = reversed(socket.getaddrinfo(host, int(port), 0, socktype))
		except Exception:
			addr = (host, int(port))
			if ":" in host:
				af = socket.AF_INET6
				addr = addr.__add__((0, 0))
			else:
				af = socket.AF_INET
			lookup = [(af, socktype, 1, 6, addr)]
		for af, socktype, proto, cn, addr in lookup:
			try:
				self._sock = socket.socket(af, socktype)
				self._sock.connect(addr)
				self._send = self._sock.sendall
				self._recv = self._sock.recv
			except socket.error as error:
				if getattr(self, "_sock", None):
					self._sock.close()
				try:
					code, error = error
				except Exception:
					code = -1
				self.DEBUG("Failed to connect to remote host %s: %s (%s)" % (repr(server), error, code), "error")
			except Exception:
				pass
			else:
				self.DEBUG("Successfully connected to remote host %s." % repr(server), "start")
				return "ok"

	def plugout(self):
		if getattr(self, "_sock", None):
			self._sock.close()
		if hasattr(self._owner, "Connection"):
			del self._owner.Connection
			self._owner.UnregisterDisconnectHandler(self.disconnected)

	def receive(self):
		try:
			data = self._recv(BUFLEN)
		except socket.sslerror as e:
			self._seen_data = 0
			if e[0] in (socket.SSL_ERROR_WANT_READ, socket.SSL_ERROR_WANT_WRITE):
				return ""
			self.DEBUG("Socket error while receiving data.", "error")
			sys.exc_clear()
			self._owner.disconnected()
			raise IOError("Disconnected!")
		except Exception:
			data = ""
		while self.pending_data(0):
			try:
				add = self._recv(BUFLEN)
			except Exception:
				break
			if not add:
				break
			data += add
		if data:
			self._seen_data = 1
			self.DEBUG(data, "got")
			if hasattr(self._owner, "Dispatcher"):
				self._owner.Dispatcher.Event("", DATA_RECEIVED, data)
		else:
			self.DEBUG("Socket error while receiving data.", "error")
			sys.exc_clear()
			self._owner.disconnected()
			raise IOError("Disconnected!")
		return data

	def send(self, data):
		if isinstance(data, unicode):
			data = data.encode("utf-8")
		elif not isinstance(data, str):
			data = ustr(data).encode("utf-8")
		with self._sequence:
			try:
				self._send(data)
			except (Exception, socket.error):
				self.DEBUG("Socket error while sending data.", "error")
				self._owner.disconnected()
			else:
				if not data.strip():
					data = repr(data)
				self.DEBUG(data, "sent")
				if hasattr(self._owner, "Dispatcher"):
					self._owner.Dispatcher.Event("", DATA_SENT, data)

	def pending_data(self, timeout=0):
		return select([self._sock], [], [], timeout)[0]

	def disconnect(self):
		self.DEBUG("Closing socket.", "stop")
		self._sock.close()

	def disconnected(self):
		self.DEBUG("Socket operation failed.", "error")

class HTTPPROXYsocket(TCPsocket):
	def __init__(self, proxy, server, use_srv=True):
		TCPsocket.__init__(self, server, use_srv)
		self.DBG_LINE = DBG_CONNECT_PROXY
		self._proxy = proxy

	def plugin(self, owner):
		owner.debug_flags.append(DBG_CONNECT_PROXY)
		return TCPsocket.plugin(self, owner)

	def connect(self, dupe=None):
		if not TCPsocket.connect(self, (self._proxy["host"], self._proxy["port"])):
			return None
		self.DEBUG("Proxy server contacted, performing authentification.", "start")
		connector = ["CONNECT %s:%s HTTP/1.0" % self._server, "Proxy-Connection: Keep-Alive", "Pragma: no-cache", "Host: %s:%s" % self._server, "User-Agent: HTTPPROXYsocket/v0.1"]
		if "user" in self._proxy and "password" in self._proxy:
			credentials = "%s:%s" % (self._proxy["user"], self._proxy["password"])
			credentials = encodestring(credentials).strip()
			connector.append("Proxy-Authorization: Basic " + credentials)
		connector.append("\r\n")
		self.send("\r\n".join(connector))
		try:
			reply = self.receive().replace("\r", "")
		except IOError:
			self.DEBUG("Proxy suddenly disconnected.", "error")
			self._owner.disconnected()
			return None
		try:
			proto, code, desc = reply.split("\n")[0].split(" ", 2)
		except Exception:
			raise error("Invalid proxy reply")
		if code != "200":
			self.DEBUG("Invalid proxy reply: %s %s %s" % (proto, code, desc), "error")
			self._owner.disconnected()
			return None
		while reply.find("\n\n") == -1:
			try:
				reply += self.receive().replace("\r", "")
			except IOError:
				self.DEBUG("Proxy suddenly disconnected.", "error")
				self._owner.disconnected()
				return None
		self.DEBUG("Authentification successfull. Jabber server contacted.", "ok")
		return "ok"

	def DEBUG(self, text, severity):
		return self._owner.DEBUG(DBG_CONNECT_PROXY, text, severity)

class TLS(PlugIn):
	def PlugIn(self, owner, now=0):
		if hasattr(owner, "TLS"):
			return None
		PlugIn.PlugIn(self, owner)
		DBG_LINE = "TLS"
		if now:
			return self._startSSL()
		if self._owner.Dispatcher.Stream.features:
			try:
				self.FeaturesHandler(self._owner.Dispatcher, self._owner.Dispatcher.Stream.features)
			except NodeProcessed:
				pass
		else:
			self._owner.RegisterHandlerOnce("features", self.FeaturesHandler, xmlns=NS_STREAMS)
		self.starttls = None

	def plugout(self, now=0):
		self._owner.UnregisterHandler("features", self.FeaturesHandler, xmlns=NS_STREAMS)
		self._owner.UnregisterHandler("proceed", self.StartTLSHandler, xmlns=NS_TLS)
		self._owner.UnregisterHandler("failure", self.StartTLSHandler, xmlns=NS_TLS)

	def FeaturesHandler(self, conn, feats):
		if not feats.getTag("starttls", namespace=NS_TLS):
			self.DEBUG("TLS unsupported by remote server.", "warn")
			return None
		self.DEBUG("TLS supported by remote server. Requesting TLS start.", "ok")
		self._owner.RegisterHandlerOnce("proceed", self.StartTLSHandler, xmlns=NS_TLS)
		self._owner.RegisterHandlerOnce("failure", self.StartTLSHandler, xmlns=NS_TLS)
		self._owner.Connection.send("<starttls xmlns=\"%s\"/>" % NS_TLS)
		raise NodeProcessed()

	def pending_data(self, timeout=0):
		return self._tcpsock._seen_data or select([self._tcpsock._sock], [], [], timeout)[0]

	def _startSSL(self):
		tcpsock = self._owner.Connection
		if sys.hexversion >= 0x20600F0:
			tcpsock._sslObj = ssl.wrap_socket(tcpsock._sock, None, None)
		else:
			tcpsock._sslObj = socket.ssl(tcpsock._sock, None, None)
			tcpsock._sslIssuer = tcpsock._sslObj.issuer()
			tcpsock._sslServer = tcpsock._sslObj.server()
		tcpsock._recv = tcpsock._sslObj.read
		tcpsock._send = tcpsock._sslObj.write
		tcpsock._seen_data = 1
		self._tcpsock = tcpsock
		tcpsock.pending_data = self.pending_data
		tcpsock._sock.setblocking(0)
		self.starttls = "success"

	def StartTLSHandler(self, conn, starttls):
		if starttls.getNamespace() != NS_TLS:
			return None
		self.starttls = starttls.getName()
		if self.starttls == "failure":
			self.DEBUG("Got starttls response: " + self.starttls, "error")
			return None
		self.DEBUG("Got starttls proceed response. Switching to TLS/SSL...", "ok")
		self._startSSL()
		self._owner.Dispatcher.PlugOut()
		dispatcher.Dispatcher().PlugIn(self._owner)
