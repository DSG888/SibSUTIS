#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys, re
reload(sys).setdefaultencoding("utf-8")

def main():
	res = {}
	for i in [5000, 10000, 15000, 20000, 25000, 30000]:
		res[i**2] = {}
	fl = os.listdir("./")
	for i in fl:
		if 0 > i.find(".o"):
			continue
		fo = open(i, "rt")
		fa = fo.read()
		fo.close()
		matrix = int(re.search("MATRIX = (\d*)\n", fa).group(1))
		serial = float(re.search("Elapsed time \(serial\): (.*) sec.", fa).group(1))
		parallel = float(re.search("Elapsed time \(parallel\): (.*) sec.", fa).group(1))
		th = int(re.search("Потоков: (\d*)\n", fa).group(1))
		res[matrix][th] = (parallel, serial)
	for i in res.keys():
		res[i]
		fl = open(str(i)+".dat", "wt")
		for j in xrange(2,9):
			fl.write(str (j) + "\t" + str(res[i][j][0] / res[i][j][1]) +"\n")
		fl.close()
	
	return




if __name__ == '__main__':
	core = getattr(sys.modules["__main__"], "__file__", None)
	if core:
		root = os.path.dirname(os.path.abspath(core))
		if root:
			os.chdir(root)
	main()
