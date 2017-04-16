#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys, re
reload(sys).setdefaultencoding("utf-8")

def main():
	RAWv1 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
	RAWv2 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
	RAWv3 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
	
	sv1 = {}
	sv2 = {}
	sv3 = {}
	
	fl = os.listdir("./")
	
	for i in fl:
		if 0 > i.find(".o"):
			continue
		fo = open(i, "rt")
		fa = fo.read()
		fo.close()
		
		th = int(re.search("Потоков: (\d*)\n", fa).group(1))
		v3 = fa[fa.rfind("===")+4:fa.rfind("Version 3")]
		fa = fa[:fa.rfind("===")]
		v2 = fa[fa.rfind("===")+4:fa.rfind("Version 2")]
		fa = fa[:fa.rfind("===")]
		v1 = fa[fa.rfind("Version: 1")+4:-1]
		
		RAWv1[th].append(float(v1[v1.rfind("Elapsed time (sec.): ") + len("Elapsed time (sec.): "):]))
		RAWv2[th].append(float(v2[v2.rfind("Elapsed time (sec.): ") + len("Elapsed time (sec.): "):]))
		RAWv3[th].append(float(v3[v3.rfind("Elapsed time (sec.): ") + len("Elapsed time (sec.): "):]))

	for i in [1, 2, 3, 4, 5, 6, 7, 8]:
		res = 0.0
		for j in RAWv1[i]:
			res += j
		res /= len(RAWv1[i])
		print i, "", len(RAWv1[i])
		sv1[i] = res

		res = 0.0
		for j in RAWv2[i]:
			res += j
		res /= len(RAWv2[i])
		print i, "", len(RAWv2[i])
		sv2[i] = res

		res = 0.0
		for j in RAWv3[i]:
			res += j
		res /= len(RAWv3[i])
		print i, "", len(RAWv3[i])
		sv3[i] = res


	flv1 = open("v1.dat", "wt")
	flv2 = open("v2.dat", "wt")
	flv3 = open("v3.dat", "wt")
	for i in [2, 3, 4, 5, 6, 7, 8]:
		flv1.write(str(i) + "\t" + str(sv1[1] / sv1[i]) +"\n")
		flv2.write(str(i) + "\t" + str(sv2[1] / sv2[i]) +"\n")
		flv3.write(str(i) + "\t" + str(sv3[1] / sv3[i]) +"\n")
	
	flv1.close()
	flv2.close()
	flv3.close()
	return




if __name__ == '__main__':
	core = getattr(sys.modules["__main__"], "__file__", None)
	if core:
		root = os.path.dirname(os.path.abspath(core))
		if root:
			os.chdir(root)
	main()
