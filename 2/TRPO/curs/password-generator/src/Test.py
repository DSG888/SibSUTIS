#!/usr/bin/python
# coding: utf-8

import sys
import PasswordGenerator
reload(sys).setdefaultencoding("utf-8")

def main():
	dics = {}
	args = PasswordGenerator.ArgParse()
	for pwd in (PasswordGenerator.genpwd(10000000, args)):
		for x in (list(pwd)):
			if dics.get(x, 0):
				dics[x] += 1
			else:
				dics[x] = 1
	A = dics.keys()
	A.sort()
	for ch in (A):
		print("\t" + ch + " : " + str(dics[ch]))
	return

main()
