#ifndef RHOMBUS_H
#define RHOMBUS_H

#include <GL/glut.h>
#include <cmath>
#include "rectangle.h"
#include "point.h"

class tRhombus : public tRectangle
{
	private:
		float _R2;
	public:
		tRhombus(float a, float b);
		void setR(float a);
		void setR2(float b);

		void setXtl(float c, float fi = 0);
		void setYtl(float c, float fi = 0);
		void setXtr(float c, float fi = 0);
		void setYtr(float c, float fi = 0);
		void setXbl(float c, float fi = 0);
		void setYbl(float c, float fi = 0);
		void setXbr(float c, float fi = 0);
		void setYbr(float c, float fi = 0);

		float getR2();
};

#endif
