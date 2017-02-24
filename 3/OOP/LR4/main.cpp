/*
Добавить к программе Занятия 3: 
Создать иерархию графических классов. Описания классов оформить в отдельном модуле.

			ТОЧКА     ОТРЕЗОК    ОКРУЖНОСТЬ	
			
			ПРЯМОУГОЛЬНИК ТРЕУГОЛЬНИК ЭЛЛИПС
			
                                    РОМБ 
			
Добавить методы движения фигур:
	a) прямолинейное движение с отражением от стенок экрана
	b) вращение вокруг центра фигуры
При описании методов движения и рисования фигур использовать статические (не виртуальные) методы.
*/

#include "main.h"
#include "point.h"
#include "line.h"
#include "rectangle.h"
#include "triangle.h"
#include "circle.h"
#include "rhombus.h"
#include "ellipse.h"

using namespace std;

tPoint p = tPoint();
tLine l = tLine(100, 100, 300, 300);
tRectangle r = tRectangle(200, 120);
tTriangle t = tTriangle(100, 0, 100, 120, 50, 240);
tCircle c = tCircle(200, 200, 100);
tRhombus rh = tRhombus(150, 100);
tEllipse e = tEllipse(150, 100);

void Display()
{
	float mr = 0, mg = 0, mb = 0;
	while (!(mr + mg + mb))
	{
		mr = rand() % 2;
		mg = rand() % 2;
		mb = rand() % 2;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(mr, mg, mb);
	switch(figure)
	{
		case point:
			glPointSize(p.getSize());
			p.draw();
			glEnd();
			break;
		case line:
			l.draw();
			glEnd();
			break;
		case rectangle:
			r.draw();

			glEnd();
			break;
		case triangle:
			glPointSize(p.getSize());
			glBegin(GL_POINTS);

			glEnd();

			t.draw();

			glEnd();
			break;
		case circle:
			c.draw();

			glEnd();
			break;
		case rhombus:
			rh.draw();

			glEnd();
			break;
		case ellipse:
			e.draw();

			glEnd();
			break;
	}

	glutSwapBuffers();
}

void timer(int = 0)
{
	if (figure == point)
	{
		Display();
		p.move();
	}
	switch(figure)
	{
		case line:
			for (size_t i = 0; i < 360; ++i)
			{
				if (l.getXl() < 0 || l.getXr() < 0 || l.getXl() > win_size || l.getXr() > win_size)
					l.setVecX(-1 * l.getVecX());
				if (l.getYl() < 0 || l.getYr() < 0 || l.getYl() > win_size || l.getYr() > win_size)
					l.setVecY(-1 * l.getVecY());
				switch (action)
				{
					case 0:
						l.move();
						break;
					case 1:
						l.rotate(i);
						break;
					case 2:
						l.move();
						l.rotate(i);
						break;
				}
				Display();
			}
			break;
		case rectangle:
			for (size_t i = 0; i < 360; i++)
			{
				if (r.getXtl() < 0 || r.getXtr() < 0 || r.getXbl() < 0 || r.getXbr() < 0)
					r.setVecX(-1 * r.getVecX());
				if (r.getYtl() < 0 || r.getYtr() < 0 || r.getYbl() < 0 || r.getYbr() < 0)
					r.setVecY(-1 * r.getVecY());
				if (r.getXtl() > win_size || r.getXtr() > win_size || r.getXbl() > win_size || r.getXbr() > win_size)
					r.setVecX(-1 * r.getVecX());
				if (r.getYtl() > win_size || r.getYtr() > win_size || r.getYbl() > win_size || r.getYbr() > win_size)
					r.setVecY(-1 * r.getVecY());
				switch (action)
				{
					case 0:
						r.move();
						break;
					case 1:
						r.rotate(i);
						break;
					case 2:
						r.move();
						r.rotate(i);
						break;
				}
				Display();
			}
			break;
		case triangle:
			for (size_t i = 0; i < 360; i++)
			{
				if (t.getV1X() < 0 || t.getV2X() < 0 || t.getV3X() < 0)
					t.setVecX(-1 * t.getVecX());
				if (t.getV1Y() < 0 || t.getV2Y() < 0 || t.getV3Y() < 0)
					t.setVecY(-1 * t.getVecY());
				if (t.getV1X() > win_size || t.getV2X() > win_size || t.getV3X() > win_size)
					t.setVecX(-1 * t.getVecX());
				if (t.getV1Y() > win_size || t.getV2Y() > win_size || t.getV3Y() > win_size)
					t.setVecY(-1 * t.getVecY());
				switch (action)
				{
					case 0:
						t.move();
						break;
					case 1:
						t.rotate(i);
						break;
					case 2:
						t.move();
						t.rotate(i);
						break;
				}
				Display();
			}
			break;
		case circle:
			if (c.getR() > c.getX() || c.getR() > (win_size - c.getX()))
				c.setVecX(-1 * c.getVecX());
			if (c.getR() > c.getY() || c.getR() > (win_size - c.getY()))
				c.setVecY(-1 * c.getVecY());
			c.move();
			Display();
			break;
		case rhombus:
			for (size_t i = 0; i < 360; i++)
			{
				if (rh.getXtl() < 0 || rh.getXtr() < 0 || rh.getXbl() < 0 || rh.getXbr() < 0)
					rh.setVecX(-1 * rh.getVecX());
				if (rh.getYtl() < 0 || rh.getYtr() < 0 || rh.getYbl() < 0 || rh.getYbr() < 0)
					rh.setVecY(-1 * rh.getVecY());
				if (rh.getXtl() > win_size || rh.getXtr() > win_size || rh.getXbl() > win_size || rh.getXbr() > win_size)
					rh.setVecX(-1 * rh.getVecX());
				if (rh.getYtl() > win_size || rh.getYtr() > win_size || rh.getYbl() > win_size || rh.getYbr() > win_size)
					rh.setVecY(-1 * rh.getVecY());
				switch (action)
				{
					case 0:
						rh.move();
						break;
					case 1:
						rh.rotate(i);
						break;
					case 2:
						rh.move();
						rh.rotate(i);
						break;
				}
				Display();
			}
			break;
		case ellipse:
			for (size_t i = 0; i < 360; i++)
			{
				if (e.getA() > e.getX() || e.getA() > (win_size - e.getX()))
				e.setVecX(-1 * e.getVecX());
				if (e.getB() > e.getY() || e.getB() > (win_size - e.getY()))
				e.setVecY(-1 * e.getVecY());
				switch (action)
				{
					case 0:
						e.move();
						break;
					case 1:
						e.rotate(i);
						break;
					case 2:
						e.move();
						e.rotate(i);
						break;
				}
				Display();
			}
			break;
	}
	glutTimerFunc(5, timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(win_size, win_size);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("4");
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, win_size, 0, win_size);
	glutDisplayFunc(Display);
	timer();
	glutMainLoop();
}
