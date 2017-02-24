#include "ellipse.h"

tEllipse::tEllipse(float A, float B)
{
	setA(A);
	setB(B);
}

void tEllipse::setA(float A)
{
	this->_A = A;
}

void tEllipse::setB(float B)
{
	this->_B = B;
}

void tEllipse::setAngle(float Angle)
{
	this->_Angle = grTOrad(Angle);
}

void tEllipse::setR()
{
	this->_R = (getA() * getB()) / (sqrt(pow(getB(), 2) * pow(cos(getAngle()), 2) + pow(getA(), 2) * pow(sin(getAngle()), 2)));
}

void tEllipse::settX()
{
	this->_tX = getX() + (getR() * cos(getAngle() + getfi()));
}

void tEllipse::settY()
{
	this->_tY = getY() + (getR() * sin(getAngle() + getfi()));
}

float tEllipse::getA()
{
	return this->_A;
}

float tEllipse::getB()
{
	return this->_B;
}

float tEllipse::getR()
{
	return this->_R;
}

float tEllipse::getAngle()
{
	return this->_Angle;
}

float tEllipse::gettX()
{
	return this->_tX;
}

float tEllipse::gettY()
{
	return this->_tY;
}

float tEllipse::grTOrad(float Gr)
{
	return Gr * M_PI / 180;
}

void tEllipse::move()
{
	this->setX(this->getX() + (this->getVecX() * 0.1));
	this->setY(this->getY() + (this->getVecY() * 0.1));
	settX();
	settY();
}

void tEllipse::setfi(float fi)
{
	this->_fi = fi;
}

float tEllipse::getfi()
{
	return this->_fi;
}

void tEllipse::rotate(float Gr)
{
	float Rad = this->grTOrad(Gr);
	setfi(Rad);
}

void tEllipse::draw()
{
	glBegin(GL_LINES);
	for (size_t i = 0; i < 360; ++i)
	{
		this->setAngle(i);
		this->setR();
		this->settX();
		this->settY();
		glVertex2f(this->gettX(), this->gettY());
		this->setAngle(i + 1);
		this->setR();
		this->settX();
		this->settY();
		glVertex2f(this->gettX(), this->gettY());
	}
}
