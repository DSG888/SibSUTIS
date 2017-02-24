#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glut.h>
#include <cmath>
#include "point.h"
#include <iostream>

class tTriangle : public tPoint
{
	private:
		float _V1X;
		float _V1Y;
		float _V2X;
		float _V2Y;
		float _V3X;
		float _V3Y;

		float _AngleV1;
		float _AngleV2;
		float _AngleV3;

		float _RV1;
		float _RV2;
		float _RV3;
	public:
		tTriangle(float R1, float A1, float R2, float A2, float R3, float A3);

		void setR(float R, int NVert);
		void setAngle(float Angle, int NVert);

		void setV1X(float c, float fi = 0);
		void setV1Y(float c, float fi = 0);
		void setV2X(float c, float fi = 0);
		void setV2Y(float c, float fi = 0);
		void setV3X(float c, float fi = 0);
		void setV3Y(float c, float fi = 0);

		float getR(int NVert);
		float getAngle(int NVert);

		float getV1X();
		float getV1Y();
		float getV2X();
		float getV2Y();
		float getV3X();
		float getV3Y();

		float grTOrad(float Gr);
		void rotate(float Gr);
		void move();
};

#endif
