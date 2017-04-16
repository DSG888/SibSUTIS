#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys, re
reload(sys).setdefaultencoding("utf-8")

def main():
	LIv1 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}

	
	sv2 = {}
	
	fl = os.listdir("./")
	
	for i in fl:
		if 0 > i.find(".o"):
			continue
		fo = open(i, "rt")
		fa = fo.read()
		fo.close()
		
		th = int(re.search("Потоков: (\d*)\n", fa).group(1))
	#	linear = float(re.search("Последовательная версия:\nResult: .*00\nElapsed time \(sec.\): (.*)\n", fa, flags=re.MULTILINE).group(1))
		parallel = float(re.search("# niters .*, total time \(sec.\): (.*)\n", fa, flags=re.MULTILINE).group(1))
		
		LIv1[th].append(parallel)

	for i in [1, 2, 3, 4, 5, 6, 7, 8]:
		res = 0.0
		for j in LIv1[i]:
			res += j
		res /= len(LIv1[i])
		print i, "", len(LIv1[i])
		sv2[i] = res



#		res = 0.0
#		for j in RAWv3[i]:
#			res += j
#		res /= len(RAWv3[i])
#		print i, "", len(RAWv3[i])
#		sv3[i] = res


	flv2 = open("v2.dat", "wt")
#	flv3 = open("v3.dat", "wt")
	for i in [2, 3, 4, 5, 6, 7, 8]:
		flv2.write(str(i) + "\t" + str(sv2[1] / sv2[i]) +"\n")
#		flv3.write(str(i) + "\t" + str(sv3[1] / sv3[i]) +"\n")
	
#	flv1.close()
	flv2.close()
#	flv3.close()
	return




if __name__ == '__main__':
	core = getattr(sys.modules["__main__"], "__file__", None)
	if core:
		root = os.path.dirname(os.path.abspath(core))
		if root:
			os.chdir(root)
	main()
