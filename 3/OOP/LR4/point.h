#ifndef POINT_H
#define POINT_H

#include <GL/glut.h>
#include <ctime>

class tPoint
{
	protected:
		float _x;
		float _y;
		float _size;

		float _vecX;
		float _vecY;
	public:
		tPoint();

		void setX(float x);
		void setY(float y);
		void setSize(float size);

		float getX();
		float getY();
		float getSize();

		void setVecX(float vecX);
		void setVecY(float vecY);
		float getVecX();
		float getVecY();

		void move();
		void draw();
};

#endif
