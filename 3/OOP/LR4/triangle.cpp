#include "triangle.h"

tTriangle::tTriangle(float R1, float A1, float R2, float A2, float R3, float A3)
{
	setR(R1, 1);
	setR(R2, 2);
	setR(R2, 3);
	setAngle(A1, 1);
	setAngle(A2, 2);
	setAngle(A3, 3);
	setV1X(this->getX());
	setV1Y(this->getY());
	setV2X(this->getX());
	setV2Y(this->getY());
	setV3X(this->getX());
	setV3Y(this->getY());
}

void tTriangle::setR(float R, int NVert)
{
	if (NVert == 1)
	{
		this->_RV1 = R;
	}
	else if (NVert == 2)
	{
		this->_RV2 = R;
	}
	else if (NVert == 3)
	{
		this->_RV3 = R;
	}
}

void tTriangle::setAngle(float Angle, int NVert)
{
	float fi = this->grTOrad(Angle);
	if (NVert == 1)
	{
		this->_AngleV1 = fi;
	}
	else if (NVert == 2)
	{
		this->_AngleV2 = fi;
	}
	else if (NVert == 3)
	{
		this->_AngleV3 = fi;
	}
}

void tTriangle::setV1X(float c, float fi)
{
	this->_V1X = c + (this->getR(1) * cos(this->getAngle(1) + fi));
}

void tTriangle::setV1Y(float c, float fi)
{
	this->_V1Y = c + (this->getR(1) * sin(this->getAngle(1) + fi));
}

void tTriangle::setV2X(float c, float fi)
{
	this->_V2X = c + (this->getR(2) * cos(this->getAngle(2) + fi));
}

void tTriangle::setV2Y(float c, float fi)
{
	this->_V2Y = c + (this->getR(2) * sin(this->getAngle(2) + fi));
}

void tTriangle::setV3X(float c, float fi)
{
	this->_V3X = c + (this->getR(3) * cos(this->getAngle(3) + fi));
}

void tTriangle::setV3Y(float c, float fi)
{
	this->_V3Y = c + (this->getR(3) * sin(this->getAngle(3) + fi));
}

float tTriangle::getR(int NVert)
{
	float R = 0;
	if (NVert == 1)
	{
		R = this->_RV1;
	}
	else if (NVert == 2)
	{
		R = this->_RV2;
	}
	else if (NVert == 3)
	{
		R = this->_RV3;
	}
	return R;
}

float tTriangle::getAngle(int NVert)
{
	float Angle = 0;
	if (NVert == 1)
	{
		Angle = this->_AngleV1;
	}
	else if (NVert == 2)
	{
		Angle = this->_AngleV2;
	}
	else if (NVert == 3)
	{
		Angle = this->_AngleV3;
	}
	return Angle;
}

float tTriangle::getV1X()
{
	return this->_V1X;
}

float tTriangle::getV1Y()
{
	return this->_V1Y;
}

float tTriangle::getV2X()
{
	return this->_V2X;
}

float tTriangle::getV2Y()
{
	return this->_V2Y;
}

float tTriangle::getV3X()
{
	return this->_V3X;
}

float tTriangle::getV3Y()
{
	return this->_V3Y;
}

float tTriangle::grTOrad(float Gr)
{
	return Gr * M_PI / 180;
}

void tTriangle::move()
{
	this->setX(this->getX() + (this->getVecX() * 0.01));
	this->setY(this->getY() + (this->getVecY() * 0.01));
	setV1X(this->getX());
	setV1Y(this->getY());
	setV2X(this->getX());
	setV2Y(this->getY());
	setV3X(this->getX());
	setV3Y(this->getY());
}

void tTriangle::rotate(float Gr)
{
	float Rad = this->grTOrad(Gr);
	setV1X(this->getX(), Rad);
	setV1Y(this->getY(), Rad);
	setV2X(this->getX(), Rad);
	setV2Y(this->getY(), Rad);
	setV3X(this->getX(), Rad);
	setV3Y(this->getY(), Rad);
}

void tTriangle::draw()
{
	glBegin(GL_LINES);
	
	glVertex2f(this->getV1X(), this->getV1Y());
	glVertex2f(this->getV2X(), this->getV2Y());

	glVertex2f(this->getV2X(), this->getV2Y());
	glVertex2f(this->getV3X(), this->getV3Y());

	glVertex2f(this->getV3X(), this->getV3Y());
	glVertex2f(this->getV1X(), this->getV1Y());
}
