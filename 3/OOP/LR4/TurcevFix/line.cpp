#include "line.h"

tLine::tLine(float X1, float Y1, float X2, float Y2)
{
	setX((X1 + X2) / 2);
	setY((Y1 + Y2) / 2);
	setR(X1, Y1);
	setAngle(X1, Y1);
	setXl(getX());
	setYl(getY());
	setXr(getX());
	setYr(getY());
}

void tLine::setR(float X, float Y)
{
	this->_R = sqrt(pow((X - this->getX()), 2) + pow((Y - this->getY()), 2));
}

void tLine::setAngle(float X, float Y)
{
	this->_Angle = atan(abs(Y - this->getY()) / abs(X - this->getX()));
}

void tLine::setXl(float c, float fi)
{
	this->_Xl = c + (this->getR() * cos(this->getAngle() + fi));
}

void tLine::setYl(float c, float fi)
{
	this->_Yl = c + (this->getR() * sin(this->getAngle() + fi));
}

void tLine::setXr(float c, float fi)
{
	this->_Xr = c + (this->getR() * cos(M_PI + this->getAngle() + fi));
}

void tLine::setYr(float c, float fi)
{
	this->_Yr = c + (this->getR() * sin(M_PI + this->getAngle() + fi));
}

float tLine::getR()
{
	return this->_R;
}

float tLine::getAngle()
{
	return this->_Angle;
}

float tLine::getXl()
{
	return this->_Xl;
}

float tLine::getYl()
{
	return this->_Yl;
}

float tLine::getXr()
{
	return this->_Xr;
}

float tLine::getYr()
{
	return this->_Yr;
}

float tLine::grTOrad(float Gr)
{
	return Gr * M_PI / 180;
}

void tLine::rotate(float Gr)
{
	float Rad = this->grTOrad(Gr);
	setXl(getX(), Rad);
	setYl(getY(), Rad);
	setXr(getX(), Rad);
	setYr(getY(), Rad);
}

void tLine::move()
{
	this->setX(this->getX() + (this->getVecX() * 0.01));
	this->setY(this->getY() + (this->getVecY() * 0.01));
	setXl(getX());
	setYl(getY());
	setXr(getX());
	setYr(getY());
}
