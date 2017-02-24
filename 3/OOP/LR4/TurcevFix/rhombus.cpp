#include "rhombus.h"

tRhombus::tRhombus(float a, float b)
{
	setR(a);
	setR2(b);
	setXtl(this->getX());
	setYtl(this->getY());
	setXtr(this->getX());
	setYtr(this->getY());
	setXbl(this->getX());
	setYbl(this->getY());
	setXbr(this->getX());
	setYbr(this->getY());
}

void tRhombus::setR(float a)
{
	this->_R = a;
}

void tRhombus::setR2(float b)
{
	this->_R2 = b;
}

void tRhombus::setXtl(float c, float fi)
{
	this->_Xtl = c + (this->getR() * cos(fi));
}

void tRhombus::setYtl(float c, float fi)
{
	this->_Ytl = c + (this->getR2() * sin(fi));
}

void tRhombus::setXtr(float c, float fi)
{
	this->_Xtr = c + (this->getR() * cos(M_PI/2 + fi));
}

void tRhombus::setYtr(float c, float fi)
{
	this->_Ytr = c + (this->getR2() * sin(M_PI/2 + fi));
}

void tRhombus::setXbl(float c, float fi)
{
	this->_Xbl = c + (this->getR() * cos(M_PI + fi));
}

void tRhombus::setYbl(float c, float fi)
{
	this->_Ybl = c + (this->getR2() * sin(M_PI + fi));
}

void tRhombus::setXbr(float c, float fi)
{
	this->_Xbr = c + (this->getR() * cos(-1 * M_PI/2 + fi));
}

void tRhombus::setYbr(float c, float fi)
{

	this->_Ybr = c + (this->getR2() * sin(-1 * M_PI/2 + fi));
}

float tRhombus::getR2()
{
	return this->_R2;
}
