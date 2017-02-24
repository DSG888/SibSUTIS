#include "main.h"
#include "circle.h"

using namespace std;

tCircle c = tCircle(200, 200, 100);

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
	c.draw();
	glEnd();
	glutSwapBuffers();
}

int x=0;

float grTOrad(float Gr)
{
	return Gr * M_PI / 180;
}

void timer(int = 0)
{
	if (c.getR() > c.getX() || c.getR() > (win_size - c.getX()))
		c.setVecX(-1 * c.getVecX());
	if (c.getR() > c.getY() || c.getR() > (win_size - c.getY()))
		c.setVecY(-1 * c.getVecY());
	
//!!!!!!!!!!!!!!
	c.setX(win_size / 2 + 200 * cos(grTOrad(x)));
	c.setY(win_size / 2 + 200 * sin(grTOrad(x)));
//!!!!!!!!!!!!!!
//	c.move();
	Display();
	
	x<359? x++ : x=0;
	
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
