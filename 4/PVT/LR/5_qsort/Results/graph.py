#!/usr/bin/env python
# -*- coding: utf-8 

from matplotlib import mlab
import pylab, re, os
import numpy

Pv1 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1s = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1u = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}

pat = "/tmp/5_qsort/s=200/100000000/"
fl = os.listdir(pat)
for i in fl:
	if 0 > i.find(".o"):
		continue
	fo = open(pat+i, "rt")
	fa = fo.read()
	fo.close()
	co = 0
	fa = fa.replace("======", "******")
	RAWTH = re.split("==+", fa, re.MULTILINE|re.DOTALL)[1:]
	for i in RAWTH:
		if (i == '+\n'):
			continue
		th = int(re.search("Потоков: (.d*)\n", i).group(1))
		i = i.split("******")
		for j in i:
			tmp2 = re.findall("Время выполнения: (.*) секунд\n", j, re.DOTALL)
			Pv1[th].append(float(tmp2[0]))

for i in [1, 2, 3, 4, 5, 6, 7, 8]:
	res = 0.0
	for j in Pv1[i]:
		res += j
	res /= len(Pv1[i])
	print i, "", len(Pv1[i])
	Pv1s[i] = res
	res = 0.0

for i in [2, 3, 4, 5, 6, 7, 8]:
	Pv1u[i] = float(Pv1s[1]/Pv1s[i])

mas1 = [Pv1u[i] for i in [2,3,4,5,6,7,8]]







Pv1 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1s = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1u = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}

pat = "/tmp/5_qsort/s=200/50000000/"
fl = os.listdir(pat)
for i in fl:
	if 0 > i.find(".o"):
		continue
	fo = open(pat+i, "rt")
	fa = fo.read()
	fo.close()
	co = 0
	fa = fa.replace("======", "******")
	RAWTH = re.split("==+", fa, re.MULTILINE|re.DOTALL)[1:]
	for i in RAWTH:
		if (i == '+\n'):
			continue
		th = int(re.search("Потоков: (.d*)\n", i).group(1))
		i = i.split("******")
		for j in i:
			tmp2 = re.findall("Время выполнения: (.*) секунд\n", j, re.DOTALL)
			Pv1[th].append(float(tmp2[0]))

for i in [1, 2, 3, 4, 5, 6, 7, 8]:
	res = 0.0
	for j in Pv1[i]:
		res += j
	res /= len(Pv1[i])
	print i, "", len(Pv1[i])
	Pv1s[i] = res
	res = 0.0

for i in [2, 3, 4, 5, 6, 7, 8]:
	Pv1u[i] = float(Pv1s[1]/Pv1s[i])

mas2 = [Pv1u[i] for i in [2,3,4,5,6,7,8]]










Pv1 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1s = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1u = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}

pat = "/tmp/5_qsort/s=200/10000000/"
fl = os.listdir(pat)
for i in fl:
	if 0 > i.find(".o"):
		continue
	fo = open(pat+i, "rt")
	fa = fo.read()
	fo.close()
	co = 0
	fa = fa.replace("======", "******")
	RAWTH = re.split("==+", fa, re.MULTILINE|re.DOTALL)[1:]
	for i in RAWTH:
		if (i == '+\n'):
			continue
		th = int(re.search("Потоков: (.d*)\n", i).group(1))
		i = i.split("******")
		for j in i:
			tmp2 = re.findall("Время выполнения: (.*) секунд\n", j, re.DOTALL)
			Pv1[th].append(float(tmp2[0]))

for i in [1, 2, 3, 4, 5, 6, 7, 8]:
	res = 0.0
	for j in Pv1[i]:
		res += j
	res /= len(Pv1[i])
	print i, "", len(Pv1[i])
	Pv1s[i] = res
	res = 0.0

for i in [2, 3, 4, 5, 6, 7, 8]:
	Pv1u[i] = float(Pv1s[1]/Pv1s[i])

mas3 = [Pv1u[i] for i in [2,3,4,5,6,7,8]]




















Pv1 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1s = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1u = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}

pat = "/tmp/5_qsort/s=4000/100000000/"
fl = os.listdir(pat)
for i in fl:
	if 0 > i.find(".o"):
		continue
	fo = open(pat+i, "rt")
	fa = fo.read()
	fo.close()
	co = 0
	fa = fa.replace("======", "******")
	RAWTH = re.split("==+", fa, re.MULTILINE|re.DOTALL)[1:]
	for i in RAWTH:
		if (i == '+\n'):
			continue
		th = int(re.search("Потоков: (.d*)\n", i).group(1))
		i = i.split("******")
		for j in i:
			tmp2 = re.findall("Время выполнения: (.*) секунд\n", j, re.DOTALL)
			Pv1[th].append(float(tmp2[0]))

for i in [1, 2, 3, 4, 5, 6, 7, 8]:
	res = 0.0
	for j in Pv1[i]:
		res += j
	res /= len(Pv1[i])
	print i, "", len(Pv1[i])
	Pv1s[i] = res
	res = 0.0

for i in [2, 3, 4, 5, 6, 7, 8]:
	Pv1u[i] = float(Pv1s[1]/Pv1s[i])

mas4 = [Pv1u[i] for i in [2,3,4,5,6,7,8]]







Pv1 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1s = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1u = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}

pat = "/tmp/5_qsort/s=4000/50000000/"
fl = os.listdir(pat)
for i in fl:
	if 0 > i.find(".o"):
		continue
	fo = open(pat+i, "rt")
	fa = fo.read()
	fo.close()
	co = 0
	fa = fa.replace("======", "******")
	RAWTH = re.split("==+", fa, re.MULTILINE|re.DOTALL)[1:]
	for i in RAWTH:
		if (i == '+\n'):
			continue
		th = int(re.search("Потоков: (.d*)\n", i).group(1))
		i = i.split("******")
		for j in i:
			tmp2 = re.findall("Время выполнения: (.*) секунд\n", j, re.DOTALL)
			Pv1[th].append(float(tmp2[0]))

for i in [1, 2, 3, 4, 5, 6, 7, 8]:
	res = 0.0
	for j in Pv1[i]:
		res += j
	res /= len(Pv1[i])
	print i, "", len(Pv1[i])
	Pv1s[i] = res
	res = 0.0

for i in [2, 3, 4, 5, 6, 7, 8]:
	Pv1u[i] = float(Pv1s[1]/Pv1s[i])

mas5 = [Pv1u[i] for i in [2,3,4,5,6,7,8]]










Pv1 = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1s = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}
Pv1u = {1:[] , 2:[], 3:[], 4:[], 5:[], 6:[], 7:[], 8:[]}

pat = "/tmp/5_qsort/s=4000/10000000/"
fl = os.listdir(pat)
for i in fl:
	if 0 > i.find(".o"):
		continue
	fo = open(pat+i, "rt")
	fa = fo.read()
	fo.close()
	co = 0
	fa = fa.replace("======", "******")
	RAWTH = re.split("==+", fa, re.MULTILINE|re.DOTALL)[1:]
	for i in RAWTH:
		if (i == '+\n'):
			continue
		th = int(re.search("Потоков: (.d*)\n", i).group(1))
		i = i.split("******")
		for j in i:
			tmp2 = re.findall("Время выполнения: (.*) секунд\n", j, re.DOTALL)
			Pv1[th].append(float(tmp2[0]))

for i in [1, 2, 3, 4, 5, 6, 7, 8]:
	res = 0.0
	for j in Pv1[i]:
		res += j
	res /= len(Pv1[i])
	print i, "", len(Pv1[i])
	Pv1s[i] = res
	res = 0.0

for i in [2, 3, 4, 5, 6, 7, 8]:
	Pv1u[i] = float(Pv1s[1]/Pv1s[i])

mas6 = [Pv1u[i] for i in [2,3,4,5,6,7,8]]


















fig, ax = pylab.subplots()
ax.set_xticks(numpy.arange(2, 9, 1))
ax.set_yticks(numpy.arange(0., 9., 0.5))

ax.plot([2, 3, 4, 5, 6, 7, 8], [2, 3, 4, 5, 6, 7, 8], label="Линейное ускорение".decode('utf-8'))
ax.plot([2, 3, 4, 5, 6, 7, 8], mas1, '-*', label="Быстрая сортировка n=100000000 s=200".decode('utf-8'), )
ax.plot([2, 3, 4, 5, 6, 7, 8], mas2, '-*', label="Быстрая сортировка n=50000000 s=200".decode('utf-8'), )
ax.plot([2, 3, 4, 5, 6, 7, 8], mas3, '-*', label="Быстрая сортировка n=10000000 s=200".decode('utf-8'), )

ax.plot([2, 3, 4, 5, 6, 7, 8], mas4, '--*', label="Быстрая сортировка n=100000000 s=4000".decode('utf-8'), )
ax.plot([2, 3, 4, 5, 6, 7, 8], mas5, '--*', label="Быстрая сортировка n=50000000 s=4000".decode('utf-8'), )
ax.plot([2, 3, 4, 5, 6, 7, 8], mas6, '--*', label="Быстрая сортировка n=10000000 s=4000".decode('utf-8'), )

ax.set_title('График зависимости ускорения от числа потоков'.decode('utf-8'))
ax.legend(loc='upper left').draggable()
ax.set_xlabel("Число потоков".decode('utf-8'))
ax.set_ylabel("Ускорение".decode('utf-8'))


ax.grid()

pylab.show()
