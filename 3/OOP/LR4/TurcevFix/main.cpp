/*

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
tEllipse e = tEllipse(50, 100);
tRectangle r = tRectangle(200, 120);
tCircle c = tCircle(200, 200, 100);
tTriangle t = tTriangle(100, 0, 100, 120, 50, 240);
tRhombus rh = tRhombus(150, 100);

int iRad = 0;
int figu = 0;
int action = 2;

void Display()
{
	if (figu > 6)
		figu = 0;

	glClear(GL_COLOR_BUFFER_BIT);
	float mr = 0, mg = 0, mb = 0;
	while (!(mr + mg + mb))
	{
		mr = rand()%2;
		mg = rand()%2;
		mb = rand()%2;
	}
glColor3f(mr, mg, mb);

	//point
	glPointSize(p.getSize());
	glColor3f(mr, mg, mb);
	glBegin(GL_POINTS);
	glVertex2f(p.getX(), p.getY());
	glEnd();

	//line
	glColor3f(mr, mg, mb);
	glBegin(GL_LINES);
	glVertex2f(l.getXl(), l.getYl());
	glVertex2f(l.getXr(), l.getYr());
	glEnd();

	//rectangle
	glColor3f(mr, mg, mb);
	glBegin(GL_LINES);
	glVertex2f(r.getXtl(), r.getYtl());
	glVertex2f(r.getXtr(), r.getYtr());
	glVertex2f(r.getXtr(), r.getYtr());
	glVertex2f(r.getXbr(), r.getYbr());
	glVertex2f(r.getXbr(), r.getYbr());
	glVertex2f(r.getXbl(), r.getYbl());
	glVertex2f(r.getXbl(), r.getYbl());
	glVertex2f(r.getXtl(), r.getYtl());
	glEnd();

	//triangle
	glColor3f(mr, mg, mb);
	glPointSize(p.getSize());
	glBegin(GL_POINTS);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(t.getV1X(), t.getV1Y());
	glVertex2f(t.getV2X(), t.getV2Y());
	glVertex2f(t.getV2X(), t.getV2Y());
	glVertex2f(t.getV3X(), t.getV3Y());
	glVertex2f(t.getV3X(), t.getV3Y());
	glVertex2f(t.getV1X(), t.getV1Y());
	glEnd();

	//rhombus
	glColor3f(mr, mg, mb);
	glBegin(GL_LINES);
	glVertex2f(rh.getXtl(), rh.getYtl());
	glVertex2f(rh.getXtr(), rh.getYtr());
	glVertex2f(rh.getXtr(), rh.getYtr());
	glVertex2f(rh.getXbl(), rh.getYbl());
	glVertex2f(rh.getXbl(), rh.getYbl());
	glVertex2f(rh.getXbr(), rh.getYbr());
	glVertex2f(rh.getXbr(), rh.getYbr());
	glVertex2f(rh.getXtl(), rh.getYtl());
	glEnd();

	//circle
	glColor3f(mr, mg, mb);
	glBegin(GL_LINES);
	for (size_t i = 0; i < 360; i++)
	{
		glVertex2f(c.getTmpX(i), c.getTmpY(i));
		glVertex2f(c.getTmpX(i + 1), c.getTmpY(i + 1));
	}
	glEnd();

	//ellipse
	glColor3f(mr, mg, mb);
	glBegin(GL_LINES);
	for (size_t i = 0; i < 360; i++)
	{
		e.setAngle(i);
		e.setR();
		e.settX();
		e.settY();
		glVertex2f(e.gettX(), e.gettY());
		e.setAngle(i+1);
		e.setR();
		e.settX();
		e.settY();
		glVertex2f(e.gettX(), e.gettY());
	}
	glEnd();


if (figu == 0)
	glutSwapBuffers();
}

void timer(int = 0)
{
// point
	p.move();
	if (p.getX() < 0 || p.getX() > win_size)
		p.setVecX(-p.getVecX());
	if (p.getY() < 0 || p.getY() > win_size)
		p.setVecY(-p.getVecY());

	++figu;
	if (l.getXl() < 0 || l.getXr() < 0 || l.getXl() > win_size || l.getXr() > win_size)
		l.setVecX(-l.getVecX());
	if (l.getYl() < 0 || l.getYr() < 0 || l.getYl() > win_size || l.getYr() > win_size)
		l.setVecY(-l.getVecY());
	switch (action)
	{
		case 0:
			l.move();
			break;
		case 1:
			l.rotate(iRad);
			break;
		case 2:
			l.move();
			l.rotate(iRad);
			break;
	}
	++figu;
	
	// line
	if (r.getXtl() < 0 || r.getXtr() < 0 || r.getXbl() < 0 || r.getXbr() < 0)
		r.setVecX(-r.getVecX());
	if (r.getYtl() < 0 || r.getYtr() < 0 || r.getYbl() < 0 || r.getYbr() < 0)
		r.setVecY(-r.getVecY());
	if (r.getXtl() > win_size || r.getXtr() > win_size || r.getXbl() > win_size || r.getXbr() > win_size)
		r.setVecX(-r.getVecX());
	if (r.getYtl() > win_size || r.getYtr() > win_size || r.getYbl() > win_size || r.getYbr() > win_size)
		r.setVecY(-r.getVecY());
	switch (action)
	{
		case 0:
			r.move();
			break;
		case 1:
			r.rotate(iRad);
			break;
		case 2:
			r.move();
			r.rotate(iRad);
			break;
	}

	++figu;
	// 2 rectangle
	if (e.getA() > e.getX() || e.getA() > (win_size - e.getX()))
	e.setVecX(-e.getVecX());
	if (e.getB() > e.getY() || e.getB() > (win_size - e.getY()))
	e.setVecY(-e.getVecY());
	switch (action)
	{
		case 0:
			e.move();
			break;
		case 1:
			e.rotate(iRad);
			break;
		case 2:
			e.move();
			e.rotate(iRad);
			break;
	}
	++figu;
// triangle
	if (t.getV1X() < 0 || t.getV2X() < 0 || t.getV3X() < 0)
		t.setVecX(-t.getVecX());
	if (t.getV1Y() < 0 || t.getV2Y() < 0 || t.getV3Y() < 0)
		t.setVecY(-t.getVecY());
	if (t.getV1X() > win_size || t.getV2X() > win_size || t.getV3X() > win_size)
		t.setVecX(-t.getVecX());
	if (t.getV1Y() > win_size || t.getV2Y() > win_size || t.getV3Y() > win_size)
		t.setVecY(-t.getVecY());
	switch (action)
	{
		case 0:
			t.move();
			break;
		case 1:
			t.rotate(iRad);
			break;
		case 2:
			t.move();
			t.rotate(iRad);
			break;
	}
	++figu;
// 4 circle
	if (c.getR() > c.getX() || c.getR() > (win_size - c.getX()))
		c.setVecX(-c.getVecX());
	if (c.getR() > c.getY() || c.getR() > (win_size - c.getY()))
		c.setVecY(-c.getVecY());
	c.move();
//	Display();
	++figu;



// 5 rhombus
	if (rh.getXtl() < 0 || rh.getXtr() < 0 || rh.getXbl() < 0 || rh.getXbr() < 0)
		rh.setVecX(-rh.getVecX());
	if (rh.getYtl() < 0 || rh.getYtr() < 0 || rh.getYbl() < 0 || rh.getYbr() < 0)
		rh.setVecY(-rh.getVecY());
	if (rh.getXtl() > win_size || rh.getXtr() > win_size || rh.getXbl() > win_size || rh.getXbr() > win_size)
		rh.setVecX(-rh.getVecX());
	if (rh.getYtl() > win_size || rh.getYtr() > win_size || rh.getYbl() > win_size || rh.getYbr() > win_size)
		rh.setVecY(-rh.getVecY());
	switch (action)
	{
		case 0:
			rh.move();
			break;
		case 1:
			rh.rotate(iRad);
			break;
		case 2:
			rh.move();
			rh.rotate(iRad);
			break;
	}
//		Display();

	++figu;


// 6 ellipse

	if (e.getA() > e.getX() || e.getA() > (win_size - e.getX()))
		e.setVecX(-e.getVecX());
	if (e.getB() > e.getY() || e.getB() > (win_size - e.getY()))
		e.setVecY(-e.getVecY());
	switch (action)
	{
		case 0:
			e.move();
			break;
		case 1:
			e.rotate(iRad);
			break;
		case 2:
			e.move();
			e.rotate(iRad);
			break;
	}
	Display();

	++figu;

	iRad <=359 ? ++iRad : iRad = 0;


	if (rand()%80 == 10)
	{
		glutTimerFunc(3000, timer, 0);
		return;
	}


	glutTimerFunc(1, timer, 0);
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
	glutTimerFunc(1, timer, 0);
	glutDisplayFunc(Display);
	
	glutMainLoop();
}
