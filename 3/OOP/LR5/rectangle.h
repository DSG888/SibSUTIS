#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/glut.h>
#include <cmath>
#include "point.h"
#include <iostream>

class tRectangle : public tPoint
{
    protected:
		float _Fi;
		float _R;

		float _Xtl;
		float _Ytl;

		float _Xtr;
		float _Ytr;

		float _Xbl;
		float _Ybl;

		float _Xbr;
		float _Ybr;

    public:

		tRectangle();
		tRectangle(float a, float b);

		void setR(float a, float b);
		void setFi(float a, float b);

		virtual void setXtl(float c, float fi = 0);
		virtual void setYtl(float c, float fi = 0);
		virtual void setXtr(float c, float fi = 0);
		virtual void setYtr(float c, float fi = 0);
		virtual void setXbl(float c, float fi = 0);
		virtual void setYbl(float c, float fi = 0);
		virtual void setXbr(float c, float fi = 0);
		virtual void setYbr(float c, float fi = 0);

		float getR();
		float getFi();

		float getXtl();
		float getYtl();
		float getXtr();
		float getYtr();
		float getXbl();
		float getYbl();
		float getXbr();
		float getYbr();

		float grTOrad(float Gr);
		virtual void rotate(float Gr);
		virtual void move();
		virtual void draw();
};

#endif
