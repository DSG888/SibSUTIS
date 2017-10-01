from collections import defaultdict
from matplotlib import mlab
import bisect, pylab, math

"""
1.0
-0.707106781187
3.06161699787e-16
0.707106781187
-1.0
0.707106781187
-2.69484193876e-15
-0.707106781187
1.0
"""

#
#xlist = mlab.frange (out_min_x, out_max_x, out_step)

in_func =  lambda x:  (math.cos(5*x))
iz = lambda x: (0.0625-0.0293291*math.sin(0.125*math.pi*x)+0.125*math.cos(0.25*math.pi*x)-0.10597*math.sin(0.375*math.pi*x)+0.125*math.cos(0.5*math.pi*x)-0.35597*math.sin(0.625*math.pi*x)+0.625*math.cos(0.75*math.pi*x)+0.220671*math.sin(0.875*math.pi*x)+0.0625*math.cos(1*math.pi*x))
zlist = mlab.frange (0, 2*math.pi, math.pi/4)

#in_func =  lambda x:  (3+x**2)

pi = math.pi

#zlist = mlab.frange (0, 10, 0.5)
hlist = mlab.frange (0, int(math.pi*2)+1, 0.01)

print iz(0)
pylab.plot(hlist, [math.cos(5*x) for x in hlist])
pylab.plot(hlist, [iz(x) for x in hlist])
#pylab.plot([0, math.pi/8, 2*math.pi/8, 3*math.pi/8, 4*math.pi/8], [in_func(x) for x in [0, math.pi/8, 2*math.pi/8, 3*math.pi/8, 4*math.pi/8] ], 'o')

pylab.show()
