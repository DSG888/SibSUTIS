#!/usr/bin/env python
# coding: utf-8

import gc
import os
import sys
import threading
import time

if __name__ == '__main__':
	import traceback
	reload(sys).setdefaultencoding("utf-8")
	core = getattr(sys.modules["__main__"], "__file__", None)
	if core:
		root = os.path.dirname(os.path.abspath(core))
		if root:
			os.chdir(root)
	import xmpp
	try:
		getPid()
	except Exception:
		pass
else:
	print ("Данный скрипт нельзя импортировать")

