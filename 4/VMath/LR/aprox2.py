#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

reload(sys).setdefaultencoding("utf-8")

from math import *
import numpy

pow_polynom = 3
x_0 = -3
n = 6
f =  lambda x:  (x)

def r(number):
	if number == -3:
		return -2
	elif number == -2:
		return -1
	elif number == -1:
		return 2
	elif number == 1:
		return 2
	elif number == 2:
		return 1
	elif number == 4:
		return -2
	else:
		return 0

f = r

res = []
for i in xrange(0, pow_polynom):
	res.append(0.)
	

def g(number, x):
	if number == 0:
		return 1
	if number == 1:
		return x*(x)
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
	print coefficients
	tmp = list(numpy.linalg.solve(coefficients, tmp))
	tmp.reverse()
	return tmp

def approx_function(coef, x):
	value = 0.
	k = pow_polynom - 1
	for i in xrange(0, pow_polynom):
		value += coef[i] * g(k, x) * 1. + g(k, 1) ;
		k = k-1
	return value


array_x_y = []
for i in xrange(0, n):
	array_x_y.append([])
	for j in xrange(0, n):
		array_x_y[i].append(0.)

#for i in xrange(0, n):
#	array_x_y[i][0] = x_0 + i * h * 1.
#	array_x_y[i][1] = f(array_x_y[i][0]) * 1.

for i in xrange(0, n):
	array_x_y[0] = [-3.,-2.,-1.,1.,2.,4.]
	array_x_y[1] = [-2.1,-1.,2.,2.,1.,-2.]

#for i in xrange(0, n):
array_x_y[0] = [-3.,-2.,0.,0.,0.,0.]
array_x_y[1] = [-2.,-1.,0.,0.,0.,0.]
array_x_y[2] = [-1.,2.,0.,0.,0.,0.]
array_x_y[3] = [1.,2.,0.,0.,0.,0.]
array_x_y[4] = [2.,1.,0.,0.,0.,0.]
array_x_y[5] = [4.,-2.,0.,0.,0.,0.]

from matplotlib import mlab

zlist = mlab.frange (-5, 5, 0.01)


res = get_coefficient(array_x_y)

import pylab
pylab.grid()

#pylab.plot(zlist, [f(x) for x in zlist ], label='График функции'.decode("utf8"))
pylab.plot(zlist, [approx_function(res, x/0.85)-2.1 for x in zlist ], label='Аппроксимация'.decode("utf8"))
#pylab.plot(glist, [approx_function(res,x) for x in glist ], "ro")
pylab.plot([-3.,-2.,-1.,1.,2.,4.], [-2.1,-1.,2.,2.,1.,-2.], "ro")

pylab.legend(loc='lower left').draggable()
pylab.show()


def main():
	
	return

if __name__ == '__main__':
	main()
