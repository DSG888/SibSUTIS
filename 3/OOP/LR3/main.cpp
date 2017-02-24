/*
ЛР 3
Задание 1.Описать класс tPoint, инкапсулирующий основные свойства и методы точки на плоскости. Создать массив из 100 точек. Нарисовать точки случайным образом случайным цветом на экране. Добавить методы движения точек:
    a) прямолинейное движение с отражением от стенок экрана
    b) случайное движение с отражением.
Задание 2. Описание класса оформить в отдельном модуле. Сделать защиту полей класса (т.е. использование полей через методы).
*/

#include "point.h"
#include "main.h"

using namespace std;

vector<tPoint> p;

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (vector<tPoint>::iterator i = p.begin(); i != p.end(); ++i)
	{
		if (i->getSize() <= 2)
		{
			glPointSize(2);
			glColor3f(i->getR(), i->getG(), i->getB());
			glBegin(GL_POINTS);
			glVertex2f(i->getX(), i->getY());
			glEnd();
		}
		else
		{
			glBegin(GL_LINES);
			glColor3f(i->getR(), i->getG(), i->getB());
			for (int a = 0; a < 360; ++a)
			{
				float x = i->getSize() * cos(a * M_PI / 180);
				float y = i->getSize() * sin(a * M_PI / 180);
				glVertex2f(i->getX() + x, i->getY() + y);
				x = i->getSize() * cos((a + 1) * M_PI / 180);
				y = i->getSize() * sin((a + 1) * M_PI / 180);
				glVertex2f(i->getX() + x, i->getY() + y);
			}
			glEnd();
		}
	}
	glutSwapBuffers();
}

void timer(int = 0)
{
	Display();
	for (vector<tPoint>::iterator i = p.begin(); i != p.end(); ++i)
	{
		for (vector<tPoint>::iterator j = p.begin(); j != p.end(); ++j)
		{
			if (i != j)
			{
				float d = sqrt(pow(i->getX() - j->getX(), 2) + pow(i->getY() - j->getY(), 2));
				if (d <= (i->getSize() + j->getSize() + 1))
				{
					float f = 99 * (i->getSize() + j->getSize() - d);
					i->setVecX(i->getVecX() + f * (i->getX() - j->getX()) / d / i->getSize() * 0.1);
					i->setVecY(i->getVecY() + f * (i->getY() - j->getY()) / d / i->getSize() * 0.1);

					j->setVecX(j->getVecX() - f * (i->getX() - j->getX()) / d / j->getSize() * 0.1);
					j->setVecY(j->getVecY() - f * (i->getY() - j->getY()) / d / j->getSize() * 0.1);
				}
			}
		}
	}

	if (interaction)
	{
		for (vector<tPoint>::iterator i = p.begin(); i != p.end(); ++i)
		{
			if (i->getX() < 0 || i->getX() > win_size)
				i->setVecX(-1 * i->getVecX());
			if (i->getY() < 0 || i->getY() > win_size)
				i->setVecY(-1 * i->getVecY());
		}
		for (vector<tPoint>::iterator i = p.begin(); i != p.end(); ++i)
			i->move();
	}
	else
	{
		for (vector<tPoint>::iterator i = p.begin(); i != p.end(); ++i)
		{
			if (i->getX() < 0)
				i->setX(i->getX() + 2);
			if (i->getY() < 0)
				i->setY(i->getY() + 2);
			if (i->getX() > win_size)
				i->setX(i->getX() - 2);
			if (i->getY() > win_size)
				i->setY(i->getY() - 2);
		}
		for (vector<tPoint>::iterator i = p.begin(); i != p.end(); ++i)
			i->chMove();
	}
	glutTimerFunc(5, timer, 0);
}

int main(int argc, char **argv)
{
	for (int i = 0; i < count_vertex; ++i)
	{
		tPoint p0 = tPoint();
		p.push_back(p0);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(win_size, win_size);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3");
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, win_size, 0, win_size);
	glutDisplayFunc(Display);
	timer();
	glutMainLoop();
}
