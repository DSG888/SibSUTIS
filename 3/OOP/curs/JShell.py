#!/usr/bin/env python
# coding: utf-8

import gc
import os
import sys
import threading
import time

AuthorizationData = [   ["abc1@jabber.org", "passw0rd1", 5222],
						["abc2@ja.ru", "passw0rd1", 5222],
						["abc3@ja.ru", "passw0rd2", 5222]	]
ADMINS = ["dsg@xmpp.ru"]
RESOURCE = "Bot"


class CJabberUsers:
	"""Список jabber клиентов"""
	def __init__(self, usr):
		"""Инициализация. Здесь проходят проверки"""
		self.users = []
		try:
			assert isinstance(usr, (list, tuple))	# Проверка типа
			for i in usr:
				assert(2 == len(i.split("@")))		# Проверка ввода
				self.users.append(i)
		except:
			print "Error. Is no jabber user!"
			exit(1)
	def __iter__(self):
		"""Итератор"""
		return self.next()
	def next(self):
		for i in self.users:
			yield i

class CAdmins(CJabberUsers):
	def __init__(self, AuthData):
		self.users = []
		try:
			assert isinstance(AuthData, (list, tuple))	# Проверка типа
			for i in AuthData:
				assert(2 == len(i[0].split("@")))	# Проверка ввода
				assert type(i[1]) == str			# Проверка типа
				assert(0 != len(i[1]))				# Пароль не может быть пустым
				assert type(i[2]) == int				# Проверка типа порта
				self.users.append([i[0], i[1], i[2] or 5222])
		except:
			print "Error. Is no jabber user!"
			exit(1)
	#Next и итератор не описывается, так как они уже унаследованы



pidFile = "pid.txt"
#USE_KEEPER = False
USE_KEEPER = True
#execfile("config", globals())
if not isinstance(USE_KEEPER, bool):
	USE_KEEPER = eval(USE_KEEPER)

def msg(destination, body):
	msg = xmpp.Message(destination, body, "chat")
	Client.send(msg)


def wget(url, filename = ""):
	if not filename:
		filename = url.split("/")[-1]
	downer = urllib.urlretrieve(url, filename)
	return filename


def eval_(args):
	try:
		result = unicode(eval(args))
	except Exception:
		result = returnExc()
	return result


def exec_(args):
	try:
		exec (unicode(args + "\n"), globals())
	except Exception:
		result = returnExc()
	else:
		result = "Done."
	return result


def pyShell(cmd):
	shell = os.popen("sh -c \"%s\" 2>&1" % cmd.encode("utf-8"))
	result = shell.read() or "Done."
	return result


hostname = pyShell("hostname")
whoami = pyShell("whoami")

def cd(_dir):
	dirname = _dir.replace("\\", os.sep)
	os.chdir(dirname)
	return "%s@%s:%s$" % (whoami, hostname, dirname)


def proxy(func):
	def wrapper(*args):
		try:
			result = func(*args)
		except Exception:
			result = returnExc()
		return result
	return wrapper


rootCMD = """sudo -S %(command)s <<EOF
%(password)s
%(password)s
EOF
"""

userCMD = """su -c "%(command)s" %(username)"""


def rootMeUp(password):
	command = "%s %s" % (sys.executable, core)
	os.popen(rootCMD % vars())


def userMeDown(user):
	command = "%s %s" % (sys.executable, core)
	os.popen(userCMD % vars())


@proxy
def msgHandler(cl, m):
	body = m.getBody()
	fJid = m.getFrom()
	jid = fJid.getStripped()
	if not m.getTimestamp() and jid in ADMINS:
		text = body.split(None, 1)
		cmd = text[0].lower()
		args = text[-1] if text[-1] != cmd else ""
		if cmd == "cd":
			msg(jid, cd(args))
		elif cmd == "exec":
			msg(jid, exec_(args))
		elif cmd == "eval":
			msg(jid, eval_(args))
		elif cmd == "sh":
			msg(jid, pyShell(args))
		elif cmd == "root":
			rootMeUp(args)
		elif cmd == "user":
			userMeDown(args)
		else: 
			msg(jid, "???")
	else: 
		msg(jid, "You are not in my admin-list...")

def restart():
	time.sleep(30)
	Print("Restart: %s\n" % returnExc(), True)
	os.execl(sys.executable, sys.executable, core)


def execute(handler, list=()):
	try:
		result = handler(*list)
	except (SystemExit, xmpp.NodeProcessed):
		result = 1
	except Exception:
		result = -1
#		crashLog(handler.func_name)
	return result


def alive_keeper():

	def alive_keeper_answer(cl, stanza):
		if xmpp.isResultNode(stanza):
			Client.aKeeper = 0

	while True:
		time.sleep(30)
		thrIds = [x.name for x in threading.enumerate()]
		if not hasattr(Client, "aKeeper"):
			Client.aKeeper = 0

		if Client.aKeeper > 5:
			Print("No answer from the server, restarting...")
			restart()
		else:
			Client.aKeeper += 1
			iq = xmpp.Iq("get", to="%s@%s/%s" % (USERNAME, SERVER, RESOURCE))
			iq.addChild("ping", namespace=xmpp.NS_PING)
			sender(iq, cb=alive_keeper_answer)


def sender(stanza, cb=None, args={}):
	if cb:
		Client.SendAndCallForResponse(stanza, cb, args)
	else:
		try:
			Client.send(stanza)
		except Exception:
#			crashLog("sender")
			restart()


def dispatcher():
	while True:
		try: 
			Client.Process(5)
			gc.collect()
		except xmpp.Conflict: 
			os._exit(0)
		except: 
			restart()


def runThread(func, args=(), name=None, att=3, delay=0):
	if delay:
		thr = threading.Timer(delay, execute, (func, args))
	else:
		thr = threading.Thread(target=execute, args=(func, args))
	name = name or func.__name__
	name = str(name) + "-" + str(time.time())
	thr.name = name
	try:
		thr.start()
	except (threading.ThreadError):
		if att:
			return runThread(func, args, name, (att - 1), delay)
#		crashLog("runThread.%s" % name)


def getPid():
	pid = os.getpid()
	if os.path.exists(pidFile) and os.access(pidFile, os.R_OK):
		oldPid = rFile(pidFile)
		if oldPid:
			print("#Завершение предыдущего экземпляра: ")
			oldPid = int(oldPid)
			if pid != oldPid:
				try:
					os.kill(oldPid, 15)
					time.sleep(3)
					os.kill(oldPid, 9)
				except OSError:
					pass
				print("%d killed.\n" % oldPid)
	if os.access(pidFile, os.W_OK):
		wFile(pidFile, str(pid))


def start(ath):
	try:
		user, server = ath[0].split("@")
		password, port = ath[1], ath[2]
	except:
		print "Ошибка конфигурации"
		return
	global Client
	Client = xmpp.Client(server, port, debug = [])
	if not Client.connect((server, port), secure=None, use_srv=False):
		print "no connect"
		return
	if not Client.auth(user, password, RESOURCE):
		print "no auth"
		return
	Client.sendInitPresence()
	for x in aminlist:
		Client.Roster.Subscribe(x)
		Client.Roster.Authorize(x)
	Client.RegisterHandler("message", msgHandler)
	Client.UnregisterDisconnectHandler(Client.DisconnectHandler)
	Client.RegisterDisconnectHandler(restart)
	print("pyShell connected")
	runThread(dispatcher)
	if USE_KEEPER:
		runThread(alive_keeper)
	while True:
		try:
			time.sleep(10)
		except KeyboardInterrupt:
			os._exit(0)

if __name__ == '__main__':
	import traceback
	reload(sys).setdefaultencoding("utf-8")
	core = getattr(sys.modules["__main__"], "__file__", None)
	if core:
		root = os.path.dirname(os.path.abspath(core))
		if root:
			os.chdir(root)
	#sys.path.insert(0, "library.zip")
	import xmpp
	try:
		getPid()
	except Exception:
		pass
	aminlist = CJabberUsers(ADMINS)
	authdatalist = CAdmins(AuthorizationData)
	for Auth in authdatalist:
		start(Auth)
else:
	print ("Данный скрипт нельзя импортировать")

