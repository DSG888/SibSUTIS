#!/usr/bin/env python
# -*- coding: utf-8 

from matplotlib import mlab
import pylab, re, os
import numpy

se = [133.354659, 133.322353, 131.888232, 131.873850, 132.234505]	# n = 150
#se = [0.806181, 0.805663, 0.805904, 0.805822, 0.806338]	# n = 10

Pv1 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv2 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv3 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv4 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv5 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}

Pv1s = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv2s = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv3s = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv4s = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv5s = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}

Pv1u = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv2u = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv3u = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv4u = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv5u = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}

pat = "/tmp/1/"
fl = os.listdir(pat)
for i in fl:
	if 0 > i.find(".o"):
		continue
	fo = open(pat+i, "rt")
	fa = fo.read()
	fo.close()

	RAWTH = re.split("===", fa, re.MULTILINE|re.DOTALL)[1:]
	for i in RAWTH:
		tmp = re.split("-=", i, re.MULTILINE|re.DOTALL)
		th = int(re.search("Потоков: (.d*)\n", tmp[0]).group(1))
		for j in tmp:
			tmp2 = re.findall("==V(.d*)==.*Elapsed time \(sec\)\: ttotal (.*),", j, re.DOTALL)
			if tmp2:
				time = float(tmp2[0][1][:tmp2[0][1].find(",")])
				Ver = int(tmp2[0][0])
				if Ver == 1:
					Pv1[th].append(time)
				if Ver == 2:
					Pv2[th].append(time)
				if Ver == 3:
					Pv3[th].append(time)
				if Ver == 4:
					Pv4[th].append(time)
				if Ver == 5:
					Pv5[th].append(time)
					

		#	for k in tmp2[0]:
			#	if len(k)>0:
			#	print tmp2[0]
	#	print len(tmp)
#		for j in tmp:
#			tmp2 = re.findall("==V(.d*)==.*Elapsed time \(sec\)\: ttotal (.*)\,", j, re.DOTALL)
#			print tmp2
		
#	print (RAWTH)
#	RAWTH = re.findall("===Потоков: (.d*)\n\n.*\n==V5\-=\n\n==\+", fa, re.MULTILINE|re.DOTALL)
#	print (RAWTH)

for i in [1, 2, 3, 4, 5, 6, 7, 8]:
	res = 0.0
	for j in Pv1[i]:
		res += j
	res /= len(Pv1[i])
	print i, "", len(Pv1[i])
	Pv1s[i] = res
	res = 0.0
	for j in Pv2[i]:
		res += j
	res /= len(Pv2[i])
	print i, "", len(Pv2[i])
	Pv2s[i] = res
	res = 0.0
	for j in Pv3[i]:
		res += j
	res /= len(Pv3[i])
	print i, "", len(Pv3[i])
	Pv3s[i] = res
	res = 0.0
	for j in Pv4[i]:
		res += j
	res /= len(Pv4[i])
	print i, "", len(Pv4[i])
	Pv4s[i] = res
	res = 0.0
	for j in Pv5[i]:
		res += j
	res /= len(Pv5[i])
	print i, "", len(Pv5[i])
	Pv5s[i] = res



res = 0.0
for i in se:
	res += i
res /= len(se)
se = res
print se

for i in [1, 2, 3, 4, 5, 6, 7, 8]:
	Pv1u[i] = se/Pv1s[i]
	Pv2u[i] = se/Pv2s[i]
	Pv3u[i] = se/Pv3s[i]
	Pv4u[i] = se/Pv4s[i]
	Pv5u[i] = se/Pv5s[i] 

"""for i in [2, 3, 4, 5, 6, 7, 8]:
	Pv1u[i] = Pv1s[1]/Pv1s[i]
	Pv2u[i] = Pv1s[1]/Pv2s[i]
	Pv3u[i] = Pv1s[1]/Pv3s[i]
	Pv4u[i] = Pv1s[1]/Pv4s[i]
	Pv5u[i] = Pv1s[1]/Pv5s[i] """

mas1 = []
mas2 = []
mas3 = []
mas4 = []
mas5 = []

for i in [2, 3, 4, 5, 6, 7, 8]:
	mas1.append (Pv1u[i])
	mas2.append (Pv2u[i])
	mas3.append (Pv3u[i])
	mas4.append (Pv4u[i])
	mas5.append (Pv5u[i])

fig, ax = pylab.subplots()
ax.set_xticks(numpy.arange(2, 9, 1))
ax.set_yticks(numpy.arange(0., 9., 0.5))

ax.plot([2, 3, 4, 5, 6, 7, 8], [2, 3, 4, 5, 6, 7, 8], label="Линейное ускорение".decode('utf-8'))
ax.plot([2, 3, 4, 5, 6, 7, 8], mas1, label="В1 Большая крит. секция".decode('utf-8'), )
ax.plot([2, 3, 4, 5, 6, 7, 8], mas2, label="В2 Директива atomic".decode('utf-8'), )
ax.plot([2, 3, 4, 5, 6, 7, 8], mas3, label="В3 N блокировок".decode('utf-8'), )
ax.plot([2, 3, 4, 5, 6, 7, 8], mas4, label="В4 Доп. выч, вместо блок.".decode('utf-8'), )
ax.plot([2, 3, 4, 5, 6, 7, 8], mas5, label="В5 Доп. память, вместо вычисл.".decode('utf-8'))


ax.set_title('График зависимости ускорения от числа потоков'.decode('utf-8'))
ax.legend(loc='upper left').draggable()
ax.set_xlabel("Число потоков".decode('utf-8'))
ax.set_ylabel("Ускорение".decode('utf-8'))


ax.grid()

pylab.show()
