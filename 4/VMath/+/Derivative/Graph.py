#!/usr/bin/env python
# -*- coding: utf-8 -*-

from matplotlib import mlab
import math, pylab
pi = math.pi

def delim(c):
	if c == ' ':
		return True
	else:
		return False

def prio(op):
	if op == "u-":
		return 5
	if op == "+" or op == "-":
		return 1
	if op == "*" or op == "/":
		return 2
	if op == "**":
		return 3
	if op in ["sin", "cos", "ln", "tg", "ctg", "arcsin", "arccos", "arctg", "arcctg"]:
		return 4
	return -1

def next(s, i):
	if i < len(s)-2 and (s[i:i+2] in ["**", "ln", "tg"]):
		return 2
	if s[i] in ["+", "-", "*", "/"]:
		return 1
	if s[i:i+3] in ["sin", "cos", "ctg"]:
		return 3
	if s[i:i+5] == "arctg":
		return 5
	if s[i:i+6] in ["arcsin", "arccos", "arcctg"]:
		return 6
	return 0

def pars(s):
	mayUnary = True
	res = ""
	op = []
	i = 0
	while i < len(s):
		if not(delim(s[i])):
			if s[i] == '(':
				op.append("(")
				mayUnary = True
			else:
				if s[i] == ')':
					while op[len(op)-1] != '(':
						res += op.pop()+" "
					op.pop()
					mayUnary = False
				else:
					t = next(s, i)
					if t != 0:
						currOp = s[i:i+t]
						if mayUnary and currOp == "-":
							currOp = "u"+currOp
						while len(op) != 0 and prio(op[len(op)-1]) >= prio(currOp):
							res += op.pop()+" "
						op.append(currOp)
						i += (t - 1)
						mayUnary = True
					else:
						if s[i] == '.' or (i < len(s) - 1 and s[i+1] == '.'):
							res += s[i]
						else:
							res += s[i] + " "
						mayUnary = False
		i += 1
	while len(op) > 0:
		res += op.pop()+" "
	return res

class Func:
	def __init__(self, left, oper=None, right=None):
		self.left = left
		self.oper = oper
		self.right = right

	def left(self):
		return self.left

	def right(self):
		return self.right

	def operation(self):
		return self.oper

	def isConst(self):
		if not(self.oper is None):
			left = self.left.isConst()
			if self.right is None:
				right = True
			else:
				right = self.right.isConst()
			if left & right:
				return True
			else:
				return False
		if self.oper is None and self.left != "x":
			return True
		else:
			return False

	def isVariable(self):
		if self.oper is None and self.left == "x":
			return True
		else:
			return False

	def toString(self):
		if self.oper is None:
			return self.left
		else:
			if isUnary(self.oper):
				if self.oper == "u-":
					return "(-("+self.left.toString()+"))"
				else:
					return "("+self.oper+"("+self.left.toString()+"))"
			else:
				return "("+self.left.toString()+") "+self.oper+" ("+self.right.toString()+")"

def isOperation(op):
	ops = ["-", "+", "*", "/", "u-", "**", "sin", "cos", "ln", "tg", "ctg", "arcsin", "arccos", "arctg", "arcctg"]
	if op in ops:
		return True
	else:
		return False

def isDigit(d):
	try:
		var = float(d)
		return True
	except(TypeError, ValueError):
		return False

def isUnary(op):
	if op in ["+", "-", "*", "/", "**"]:
		return False
	else:
		return True

class FunctionTree:
	def buildTree(self, s):
		words = s.split()
		stack = []
		for word in words:
			if isDigit(word) or word == "x" or word == "e":
				stack.append(Func(word))
			else:
				stack.append(word)

		nodes = []
		for el in stack:
			if isOperation(el):
				if el in ["+", "-", "*", "/", "**"]:
					top1 = nodes.pop()
					top2 = nodes.pop()
					nodes.append(Func(top2, el, top1))
				else:
					top = nodes.pop()
					node = Func(top, el)
					nodes.append(node)
			else:
				nodes.append(el)
		self.root = nodes.pop()

	def __init__(self, s):
		self.root = None
		self.buildTree(pars(s))

	def derivative(self):
		return self._derivative(self.root)

	def _unaryDerivative(self, f, par):
		if f == "u-":
			return "-("+par+")"
		if f == "sin":
			return "cos("+par+")"
		if f == "cos":
			return "-sin("+par+")"
		if f == "tg":
			return "1 / ((cos("+par+")) ** 2)"
		if f == "ctg":
			return "(-1) / ((sin("+par+")) ** 2)"
		if f == "arcsin":
			return "1 / ((1 - ("+par+") ** 2) ** (0.5))"
		if f == "arccos":
			return "(-1) / ((1 - ("+par+") ** 2) ** (0.5))"
		if f == "arctg":
			return "1 / (1 + ("+par+") ** 2)"
		if f == "arcctg":
			return "(-1) / (1 + ("+par+") ** 2)"
		if f == "ln":
			return "1/("+par+")"

	def _derivative(self, node):
		if node.isConst():
			return "0"
		if node.isVariable():
			return "1"
		if node.operation() == "u-":
			return "-("+self._derivative(node.left)+")"
		if isUnary(node.operation()):
			return "("+self._unaryDerivative(node.operation(), node.left.toString())+") * ("+self._derivative(node.left)+")"
		if node.operation() == "+" or node.operation() == "-":
			return "(("+self._derivative(node.left) + ") " + node.operation() + " (" + self._derivative(node.right)+"))"
		if node.operation() == "*":
			return "(("+self._derivative(node.left)+") * ("+node.right.toString()+")) + (("+node.left.toString()+") * ("+self._derivative(node.right)+"))"
		if node.operation() == "/":
			return "((("+self._derivative(node.left)+") * ("+node.right.toString()+")) - ("+node.left.toString()+") * ("+self._derivative(node.right) + ")) / (("+node.right.toString()+") ** 2)"
		if node.operation() == "**":
			if not(node.left.isConst()) and node.right.isConst():
				return "("+node.right.toString()+") * ("+node.left.toString()+") ** (("+node.right.toString()+") - 1) * ("+self._derivative(node.left)+")"
			if node.left.isConst() and not(node.right.isConst()):
				if node.left.left == "e":
					return "("+node.toString()+") * ("+self._derivative(node.right)+")"
				else:
					return "("+node.toString()+") * ln("+node.left.toString()+") * ("+self._derivative(node.right)+")"
			if not(node.left.isConst()) and not(node.right.isConst()):
				node1 = Func(node.left, "ln")
				node2 = Func(node1, "*", node.right)
				node3 = Func(Func("e"), "**", node2)
				return self._derivative(node3)

from math import *
tg = tan
ln = log

def derivative(s):
	tree = FunctionTree(s.strip())
	return tree.derivative()


mini = -10
maxi = 10


pzlist = mlab.frange (mini, maxi, 0.01)


funca = "x**2"
funca = "x**sin(x)*cos(x)"
in_func =  lambda x:  (eval(funca))
in_funcp =  lambda x:  (eval(derivative(funca)))
print derivative(funca)
pro = [0]




jl = []
todel = []
for i in pzlist:
	try:
		jl.append(in_func(i))
	except:
		todel.append(i)
pzlist = list(set(pzlist) - set(todel))
pzlist.sort()




xlist = list(pzlist)




todel = []
for i in xrange(1, len(xlist)):
	try:
		pro.append(  (in_func(xlist[i]) - in_func(xlist[i-1]))  / (xlist[i]  - xlist[i-1]) )
	except:
		todel.append(xlist[i])
xlist = list(set(xlist) - set(todel))
xlist.sort()





rxlist = list(xlist)




pl = []
todel = []
for i in rxlist:
	try:
		pl.append(in_funcp(i))
	except:
		todel.append(i)
rxlist = list(set(rxlist) - set(todel))
rxlist.sort()


pylab.grid()
pylab.plot(pzlist, jl, label='График '.decode("utf8")+ funca)
pylab.plot(rxlist, pl, lw=3, label=('Производная'.decode("utf8")), color = '#ff0000')
pylab.plot(xlist[1:], pro[1:], 'g--', lw=1, label='Произв. по точкам'.decode("utf8"))
pylab.legend(loc='lower left').draggable()

pylab.show()

#for line in inp:
#	out.write(derivative(line)+"\n")

