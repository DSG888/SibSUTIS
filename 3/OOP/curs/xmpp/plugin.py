class PlugIn:
	def __init__(self):
		self._exported_methods = []
		self.DBG_LINE = self.__class__.__name__.lower()

	def PlugIn(self, owner):
		self._owner = owner
		if self.DBG_LINE not in owner.debug_flags:
			owner.debug_flags.append(self.DBG_LINE)
		self.DEBUG("Plugging %s into %s" % (self, self._owner), "start")
		if hasattr(owner, self.__class__.__name__):
			return self.DEBUG("Plugging ignored: another instance already plugged.", "error")
		self._old_owners_methods = []
		for method in self._exported_methods:
			if hasattr(owner, method.__name__):
				self._old_owners_methods.append(getattr(owner, method.__name__))
			setattr(owner, method.__name__, method)
		setattr(owner, self.__class__.__name__, self)
		if hasattr(self, "plugin"):
			return self.plugin(owner)

	def PlugOut(self):
		self.DEBUG("Plugging %s out of %s." % (self, self._owner), "stop")
		if hasattr(self, "plugout"):
			rn = self.plugout()
		else:
			rn = None
		self._owner.debug_flags.remove(self.DBG_LINE)
		for method in self._exported_methods:
			delattr(self._owner, method.__name__)
		for method in self._old_owners_methods:
			setattr(self._owner, method.__name__, method)
		delattr(self._owner, self.__class__.__name__)
		return rn

	def DEBUG(self, text, severity="info"):
		self._owner.DEBUG(self.DBG_LINE, text, severity)
