#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

reload(sys).setdefaultencoding("utf-8")

from math import *
import numpy

pow_polynom = 3
x_0 = 0
n = 3
h = 1
f =  lambda x:  (x*(x))

res = []
for i in xrange(0, pow_polynom):
	res.append(0.)
	

def g(number, x):
	if number == 0:
		return 1
	if number == 1:
		return sqrt(x)
	if number == 2:
		return x


def get_coefficient(array):
	coefficients = []
	for i in xrange(0, pow_polynom):
		coefficients.append([])
		for j in xrange(0, pow_polynom ):
			coefficients[i].append(0.)
	for i in xrange(0, pow_polynom):
		for j in xrange(0, pow_polynom):
			for k in xrange(0, n):
				coefficients[i][j] += g(i, array[k][0]) * g(j, array[k][0]) * 1.
	tmp = []
	for i in xrange(0, pow_polynom):
		tmp.append(0.)
	for i in xrange(0, pow_polynom):
		for j in xrange(0, n):
			tmp[i] += array[j][1] * g(i, array[j][0]) * 1.
	tmp = list(numpy.linalg.solve(coefficients, tmp))
	tmp.reverse()
	return tmp

def approx_function(coef, x):
	value = 0.
	k = pow_polynom - 1
	for i in xrange(0, pow_polynom):
		value += coef[i] * g(k, x) * 1.;
		k = k-1
	return value


array_x_y = []
for i in xrange(0, n):
	array_x_y.append([])
	for j in xrange(0, n):
		array_x_y[i].append(0.)

for i in xrange(0, n):
	array_x_y[i][0] = x_0 + i * h * 1.
	array_x_y[i][1] = f(array_x_y[i][0]) * 1.

from matplotlib import mlab

zlist = mlab.frange (0, 5, 0.01)
glist= list(xrange(x_0, n, h))

res = get_coefficient(array_x_y)

import pylab
pylab.grid()

pylab.plot(zlist, [f(x) for x in zlist ], label='График функции'.decode("utf8"))
pylab.plot(zlist, [approx_function(res, x) for x in zlist ], label='Аппроксимация'.decode("utf8"))
pylab.plot(glist, [approx_function(res,x) for x in glist ], "ro")
pylab.legend(loc='lower left').draggable()
pylab.show()


def main():
	
	return

if __name__ == '__main__':
	main()
