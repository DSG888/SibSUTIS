import xml.parsers.expat

XML_ls = (("&", "&amp;"), ("<", "&lt;"), (">", "&gt;"), ('"', "&quot;"), ("'", "&apos;"))

def XMLescape(body):
	for char, edef in XML_ls:
		body = body.replace(char, edef)
	return body.strip()

ENCODING = "utf-8"

def ustr(what):
	if isinstance(what, unicode):
		return what
	try:
		what = what.__str__()
	except AttributeError:
		what = str(what)
	if not isinstance(what, unicode):
		return unicode(what, ENCODING)
	return what

class Node(object):
	FORCE_NODE_RECREATION = 0

	def __init__(self, tag=None, attrs={}, payload=[], parent=None, nsp=None, node_built=False, node=None):
		if node:
			if self.FORCE_NODE_RECREATION and isinstance(node, Node):
				node = str(node)
			if not isinstance(node, Node):
				node = NodeBuilder(node, self)
				node_built = True
			else:
				self.name, self.namespace, self.attrs, self.data, self.kids, self.parent, self.nsd = node.name, node.namespace, {}, [], [], node.parent, {}
				for key in node.attrs.keys():
					self.attrs[key] = node.attrs[key]
				for data in node.data:
					self.data.append(data)
				for kid in node.kids:
					self.kids.append(kid)
				for k, v in node.nsd.items():
					self.nsd[k] = v
		else:
			self.name, self.namespace, self.attrs, self.data, self.kids, self.parent, self.nsd = "tag", "", {}, [], [], None, {}
		if parent:
			self.parent = parent
		self.nsp_cache = {}
		if nsp:
			for k, v in nsp.items():
				self.nsp_cache[k] = v
		for attr, val in attrs.items():
			if attr == "xmlns":
				self.nsd[""] = val
			elif attr.startswith("xmlns:"):
				self.nsd[attr[6:]] = val
			self.attrs[attr] = attrs[attr]
		if tag:
			if node_built:
				pfx, self.name = ([""] + tag.split(":"))[-2:]
				self.namespace = self.lookup_nsp(pfx)
			elif " " in tag:
				self.namespace, self.name = tag.split()
			else:
				self.name = tag
		if isinstance(payload, basestring):
			payload = [payload]
		for i in payload:
			if isinstance(i, Node):
				self.addChild(node=i)
			else:
				self.data.append(ustr(i))

	def lookup_nsp(self, pfx=""):
		ns = self.nsd.get(pfx, None)
		if ns is None:
			ns = self.nsp_cache.get(pfx, None)
		if ns is None:
			if self.parent:
				ns = self.parent.lookup_nsp(pfx)
				self.nsp_cache[pfx] = ns
			else:
				return "http://www.gajim.org/xmlns/undeclared"
		return ns

	def __str__(self, fancy=0):
		s = (fancy - 1) * 2 * " " + "<" + self.name
		if self.namespace:
			if not self.parent or self.parent.namespace != self.namespace:
				if "xmlns" not in self.attrs:
					s += " xmlns=\"%s\"" % self.namespace
		for key in self.attrs.keys():
			val = ustr(self.attrs[key])
			s += " %s=\"%s\"" % (key, XMLescape(val))
		s += ">"
		cnt = 0
		if self.kids:
			if fancy:
				s += "\n"
			for a in self.kids:
				if not fancy and (len(self.data) - 1) >= cnt:
					s += XMLescape(self.data[cnt])
				elif (len(self.data) - 1) >= cnt:
					s += XMLescape(self.data[cnt].strip())
				if isinstance(a, Node):
					s += a.__str__(fancy and fancy + 1)
				elif a:
					s += a.__str__()
				cnt += 1
		if not fancy and (len(self.data) - 1) >= cnt:
			s += XMLescape(self.data[cnt])
		elif (len(self.data) - 1) >= cnt:
			s += XMLescape(self.data[cnt].strip())
		if not self.kids and s.endswith(">"):
			s = s[:-1] + " />"
			if fancy:
				s += "\n"
		else:
			if fancy and not self.data:
				s += (fancy - 1) * 2 * " "
			s += "</" + self.name + ">"
			if fancy:
				s += "\n"
		return s

	def getCDATA(self):
		s = ""
		cnt = 0
		if self.kids:
			for a in self.kids:
				s += self.data[cnt]
				if a:
					s += a.getCDATA()
				cnt += 1
		if (len(self.data) - 1) >= cnt:
			s += self.data[cnt]
		return s

	def addChild(self, name=None, attrs={}, payload=[], namespace=None, node=None):
		if "xmlns" in attrs:
			raise AttributeError("Use namespace=x instead of attrs={\"xmlns\": x}")
		if node:
			newnode = node
			node.parent = self
		else:
			newnode = Node(tag=name, parent=self, attrs=attrs, payload=payload)
		if namespace:
			newnode.setNamespace(namespace)
		self.kids.append(newnode)
		self.data.append("")
		return newnode

	def addData(self, data):
		self.data.append(ustr(data))
		self.kids.append(None)

	def clearData(self):
		self.data = []

	def delAttr(self, key):
		del self.attrs[key]

	def delChild(self, node, attrs={}):
		if not isinstance(node, Node):
			node = self.getTag(node, attrs)
		self.kids[self.kids.index(node)] = None
		return node

	def getAttrs(self):
		return self.attrs

	def getAttr(self, key):
		try:
			attr = self.attrs[key]
		except Exception:
			attr = None
		return attr

	def getChildren(self):
		return self.kids

	def getData(self):
		return "".join(self.data)

	def getName(self):
		return self.name

	def getNamespace(self):
		return self.namespace

	def getParent(self):
		return self.parent

	def getPayload(self):
		pl = []
		for i in xrange(max(len(self.data), len(self.kids))):
			if i < len(self.data) and self.data[i]:
				pl.append(self.data[i])
			if i < len(self.kids) and self.kids[i]:
				pl.append(self.kids[i])
		return pl

	def getTag(self, name, attrs={}, namespace=None):
		return self.getTags(name, attrs, namespace, one=1)

	def getTagAttr(self, tag, attr):
		try:
			attr = self.getTag(tag).attrs[attr]
		except Exception:
			attr = None
		return attr

	def getTagData(self, tag):
		try:
			data = self.getTag(tag).getData()
		except Exception:
			data = None
		return data

	def getTags(self, name, attrs={}, namespace=None, one=0):
		nodes = []
		for node in self.kids:
			if not node:
				continue
			if namespace and namespace != node.getNamespace():
				continue
			if node.getName() == name:
				for key in attrs.keys():
					if key not in node.attrs or node.attrs[key] != attrs[key]:
						break
				else:
					nodes.append(node)
			if one and nodes:
				return nodes[0]
		if not one:
			return nodes

	def iterTags(self, name, attrs={}, namespace=None):
		for node in self.kids:
			if not node:
				continue
			if namespace is not None and namespace != node.getNamespace():
				continue
			if node.getName() == name:
				for key in attrs.keys():
					if key not in node.attrs or node.attrs[key] != attrs[key]:
						break
				else:
					yield node

	def setAttr(self, key, val):
		self.attrs[key] = val

	def setData(self, data):
		self.data = [ustr(data)]

	def setName(self, val):
		self.name = val

	def setNamespace(self, namespace):
		self.namespace = namespace

	def setParent(self, node):
		self.parent = node

	def setPayload(self, payload, add=0):
		if isinstance(payload, basestring):
			payload = [payload]
		if add:
			self.kids += payload
		else:
			self.kids = payload

	def setTag(self, name, attrs={}, namespace=None):
		node = self.getTags(name, attrs, namespace=namespace, one=1)
		if not node:
			node = self.addChild(name, attrs, namespace=namespace)
		return node

	def setTagAttr(self, tag, attr, val):
		try:
			self.getTag(tag).attrs[attr] = val
		except Exception:
			self.addChild(tag, attrs={attr: val})

	def setTagData(self, tag, val, attrs={}):
		try:
			self.getTag(tag, attrs).setData(ustr(val))
		except Exception:
			self.addChild(tag, attrs, payload=[ustr(val)])

	def has_attr(self, key):
		return key in self.attrs

	def __getitem__(self, item):
		return self.getAttr(item)

	def __setitem__(self, item, val):
		return self.setAttr(item, val)

	def __delitem__(self, item):
		return self.delAttr(item)

	def __getattr__(self, attr):
		if attr == "T":
			self.T = T(self)
			return self.T
		if attr == "NT":
			self.NT = NT(self)
			return self.NT
		raise AttributeError()

class T:
	def __init__(self, node):
		self.__dict__["node"] = node

	def __getattr__(self, attr):
		return self.node.getTag(attr)

	def __setattr__(self, attr, val):
		if isinstance(val, Node):
			Node.__init__(self.node.setTag(attr), node=val)
		else:
			return self.node.setTagData(attr, val)

	def __delattr__(self, attr):
		return self.node.delChild(attr)

class NT(T):
	def __getattr__(self, attr):
		return self.node.addChild(attr)

	def __setattr__(self, attr, val):
		if isinstance(val, Node):
			self.node.addChild(attr, node=val)
		else:
			return self.node.addChild(attr, payload=[val])

DBG_NODEBUILDER = "nodebuilder"

class NodeBuilder:
	def __init__(self, data=None, initial_node=None):
		self.DEBUG(DBG_NODEBUILDER, "Preparing to handle incoming XML stream.", "start")
		self._parser = xml.parsers.expat.ParserCreate()
		self._parser.StartElementHandler = self.starttag
		self._parser.EndElementHandler = self.endtag
		self._parser.CharacterDataHandler = self.handle_cdata
		self._parser.StartNamespaceDeclHandler = self.handle_namespace_start
		self._parser.buffer_text = True
		self.Parse = self._parser.Parse
		self.__depth = 0
		self.__last_depth = 0
		self.__max_depth = 0
		self._dispatch_depth = 1
		self._document_attrs = None
		self._document_nsp = None
		self._mini_dom = initial_node
		self.last_is_data = 1
		self._ptr = None
		self.data_buffer = None
		self.streamError = ""
		if data:
			self._parser.Parse(data, 1)

	def check_data_buffer(self):
		if self.data_buffer:
			self._ptr.data.append("".join(self.data_buffer))
			del self.data_buffer[:]
			self.data_buffer = None

	def destroy(self):
		self.check_data_buffer()
		self._parser.StartElementHandler = None
		self._parser.EndElementHandler = None
		self._parser.CharacterDataHandler = None
		self._parser.StartNamespaceDeclHandler = None

	def starttag(self, tag, attrs):
		self.check_data_buffer()
		self._inc_depth()
		self.DEBUG(DBG_NODEBUILDER, "DEPTH -> %i , tag -> %s, attrs -> %s" % (self.__depth, tag, repr(attrs)), "down")
		if self.__depth == self._dispatch_depth:
			if not self._mini_dom:
				self._mini_dom = Node(tag=tag, attrs=attrs, nsp=self._document_nsp, node_built=True)
			else:
				Node.__init__(self._mini_dom, tag=tag, attrs=attrs, nsp=self._document_nsp, node_built=True)
			self._ptr = self._mini_dom
		elif self.__depth > self._dispatch_depth:
			self._ptr.kids.append(Node(tag=tag, parent=self._ptr, attrs=attrs, node_built=True))
			self._ptr = self._ptr.kids[-1]
		if self.__depth == 1:
			self._document_attrs = {}
			self._document_nsp = {}
			nsp, name = ([""] + tag.split(":"))[-2:]
			for attr, val in attrs.items():
				if attr == "xmlns":
					self._document_nsp[""] = val
				elif attr.startswith("xmlns:"):
					self._document_nsp[attr[6:]] = val
				else:
					self._document_attrs[attr] = val
			ns = self._document_nsp.get(nsp, "http://www.gajim.org/xmlns/undeclared-root")
			try:
				self.stream_header_received(ns, name, attrs)
			except ValueError:
				self._document_attrs = None
				raise
		if not self.last_is_data and self._ptr.parent:
			self._ptr.parent.data.append("")
		self.last_is_data = 0

	def endtag(self, tag):
		self.DEBUG(DBG_NODEBUILDER, "DEPTH -> %i , tag -> %s" % (self.__depth, tag), "up")
		self.check_data_buffer()
		if self.__depth == self._dispatch_depth:
			if self._mini_dom and self._mini_dom.getName() == "error":
				self.streamError = self._mini_dom.getChildren()[0].getName()
			self.dispatch(self._mini_dom)
		elif self.__depth > self._dispatch_depth:
			self._ptr = self._ptr.parent
		else:
			self.DEBUG(DBG_NODEBUILDER, "Got higher than dispatch level. Stream terminated?", "stop")
		self._dec_depth()
		self.last_is_data = 0
		if not self.__depth:
			self.stream_footer_received()

	def handle_cdata(self, data):
		self.DEBUG(DBG_NODEBUILDER, data, "data")
		if self.last_is_data:
			if self.data_buffer:
				self.data_buffer.append(data)
		elif self._ptr:
			self.data_buffer = [data]
			self.last_is_data = 1

	def handle_namespace_start(self, prefix, uri):
		self.check_data_buffer()

	def DEBUG(self, level, text, comment=None):


	def getDom(self):
		self.check_data_buffer()
		return self._mini_dom

	def dispatch(self, stanza):


	def stream_header_received(self, ns, tag, attrs):
		self.check_data_buffer()

	def stream_footer_received(self):
		self.check_data_buffer()

	def has_received_endtag(self, level=0):
		return self.__depth <= level and self.__max_depth > level

	def _inc_depth(self):
		self.__last_depth = self.__depth
		self.__depth += 1
		self.__max_depth = max(self.__depth, self.__max_depth)

	def _dec_depth(self):
		self.__last_depth = self.__depth
		self.__depth -= 1

def XML2Node(xml):
	return NodeBuilder(xml).getDom()

def BadXML2Node(xml):
	return NodeBuilder(xml).getDom()
