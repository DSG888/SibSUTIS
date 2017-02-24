#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/glut.h>
#include <cmath>
#include "point.h"

class tCircle : public tPoint
{
	private:
		float _R;
	public:
		tCircle(float X, float Y, float R);

		void setR(float R);
		float getR();

		float getTmpX(float fi);
		float getTmpY(float fi);
		float grTOrad(float Gr);

		void move();
};

#endif
