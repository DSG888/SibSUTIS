#!/usr/bin/env python
# -*- coding: utf-8 -*-

from collections import defaultdict
from matplotlib import mlab
import bisect, pylab, math


def rs(dots):
    for i in range(len(dots)): splines[i].x, splines[i].a = dots[i].x, dots[i].y

    alpha, beta = [defaultdict(lambda: 0.), defaultdict(lambda: 0.)]

    for i in range(1, len(dots)-1):
        C = 4. * in_step
        F = 6. * ((dots[i + 1].y - dots[i].y) / in_step - (dots[i].y - dots[i - 1].y) / in_step)
        z = (in_step* alpha[i - 1] + C)
        alpha[i] = -in_step / z
        beta[i] = (F - in_step* beta[i - 1]) / z;

    for i in reversed(range(1, len(dots) - 1)): splines[i].c = alpha[i] * splines[i+1].c + beta[i]

    for i in reversed(range(1, len(dots))):
        hi = dots[i].x - dots[i-1].x
        splines[i].d = (splines[i].c - splines[i-1].c) / hi
        splines[i].b = hi * (2.0 * splines[i].c + splines[i - 1].c) / 6.0 + (dots[i].y - dots[i-1].y) / hi


def drange(start, stop, step):
    while start < stop: yield start; start += step;

class Dot:
    def __init__(self, x, y): self.x, self.y = [x, y]

class Tuple: a, b, c, d, x = [0., 0., 0., 0., 0.]

def newton(x_p, y_p):
    n = len(x_p)
    c = []
    for i in range(n):
        c.append(y_p[i])
    # Определение коэффициентов
    for k in range(1, n):
        for i in range(n-1, k-1, -1):
            c[i] = float(c[i] - c[i-1])/float(x_p[i] - x_p[i-k])


    # Строим полином по коэффициентам и значениям x
    def P(x):
        poly = 0
        for i in range(n):
            temp = 0
            temp += c[i]
            if i > 0:
                for k in range(i, 0, -1):
                    temp *= (x-x_p[k-1])
            poly += temp
        
        return poly
	print c
    return P

def calc(x):
    distribution = sorted([t[1].x for t in splines.items()])
    indx = bisect.bisect_left(distribution, x)
    if indx == len(distribution): return 0
    dx = x - splines[indx].x
    return splines[indx].a + splines[indx].b * dx + splines[indx].c * dx**2 / 2. + splines[indx].d * dx**3 / 6.




in_func =  lambda x:  (x**3)+1
in_min_x = 0
in_max_x = 10
in_step = 0.01

out_min_x = 0
out_max_x = 10
out_step = 0.0001





splines = defaultdict(lambda: Tuple())
rs(map(lambda x: Dot(x, in_func(x)), [x for x in drange(in_min_x, in_max_x+1, in_step)]))

#
#for x in drange(out_min_x, out_max_x, out_step):
#    print str(x) + ';' + str(calc(x))

#
xlist = mlab.frange (out_min_x, out_max_x, out_step)
zlist = mlab.frange (out_min_x, out_max_x, 0.001)

mlist = mlab.frange (out_min_x, out_max_x, 1)

print newton(mlist, [calc(x) for x in mlist])

pylab.plot(xlist, [in_func(x) for x in xlist])
pylab.plot(mlist, [in_func(x) for x in mlist ], 'o')
pylab.plot(zlist, [calc(x) for x in zlist])
pylab.plot(color='b', alpha=0.5, linestyle='', linewidth=0.5)


pylab.show()
