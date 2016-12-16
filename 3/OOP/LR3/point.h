#ifndef POINT_H
#define POINT_H

#include <GL/glut.h>
#include <ctime>


class tPoint
{
	private:
		float _x;
		float _y;
		float _size;

		float _r;
		float _g;
		float _b;

		float _vecX;
		float _vecY;
	public:
		tPoint();

		void setX(float x);
		void setY(float y);
		void setSize(float size);
		void setR(float r);
		void setG(float g);
		void setB(float b);

		float getX();
		float getY();
		float getSize();
		float getR();
		float getG();
		float getB();

		void setVecX(float vecX);
		void setVecY(float vecY);
		float getVecX();
		float getVecY();
		void move();
		void chMove();
};

#endif
