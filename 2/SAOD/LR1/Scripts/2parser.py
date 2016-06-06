#!/usr/bin/python
# coding: utf-8

import os
import sys, re
import traceback
reload(sys).setdefaultencoding("utf-8")
debug = True

def main():
	f = open("./RESULT.txt","rt")
	RAW = f.read()
	f.close()
	mas = re.findall(".*Алгоритм сортировки: (.*)\n.*Создан случайный массив из (.*) элементов\n.*Время выполнения: (.*) секунд.*\n", RAW, re.MULTILINE)
	S = {}
	for el in mas:
		if not(el[0] in S.keys()):
			S [el[0]] = []
		S[el[0]].append (str(el[1] + "\t" + el[2]))
	for el in S:
		f = open("./" + el + ".dat","wt")
		for z in S[el]:
			f.write(z+"\n")
		f.close()
	return




if __name__ == '__main__':
	core = getattr(sys.modules["__main__"], "__file__", None)
	if core:
		root = os.path.dirname(os.path.abspath(core))
		if root:
			os.chdir(root)
	try:
		main()
	except:
		if debug:
			try:
				print traceback.print_exc()
			except:
				pass
