#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>

#define N 6

float y0[N][N] = {0}, x0[N];

float func(float x)
{
	return (1 / sqrt(x));
}

float pfn(float x, float step)
{
	int i, j;
	float y, k, q = 0, f;
	y = 0;
	/*y=y0[N-1][0];*/
	q = (x - x0[N - 1]) / step;
	f = 1;
	k = 1;
	for (i = 0; i < N; ++i)
	{
		y += (y0[N - i - 1][i] / f) * k;
		k *= (q++);
		f *= (i + 1);
	}
	return (y);
}

void main()
{
	int j, i1, x1, y1, k;
	float y, x = 1, i, step;
	int gd = 0, gm;

	clrscr();
	printf("Введите значение X0: ");
	scanf("%f", &x0[0]);
	y0[0][0] = func(x0[0]);
	printf("Введите шаг: ");
	scanf("%f", &step);
	for (j = 1; j < N; ++j)
	{
		x0[j] = x0[j - 1] + step;
		y0[j][0] = func(x0[j]);
	}
	for (k = 1; k < N; ++k)
		 for (j = 0; j < N; ++j)
			y0[j][k] = y0[j + 1][k - 1] - y0[j][k - 1];
	clrscr();
	initgraph(&gd, &gm, "..");
	cleardevice();

	outtextxy(30, 40, "Y");
	outtextxy(600, 400, "X");

	line(40, 40, 40, 400);
	line(40, 400, 600, 400);

	for(x1 = 40, i = 0; i < 8; ++i)
	{
		x1 += 40;
		line(x1, 398, x1, 402);
	}
	for(y1 = 400, i = 0; i < N; ++i)
	{
		y1 -= 40;
		line(38, y1, 42, y1);
	}

	moveto(40, 400);
	setcolor(BLUE);
	for(i = 0.1; i < 70; ++i)
		lineto(40 + (i * 0.2) * 40, 400 - (int)(func(i * 0.2) * 40));

	moveto(40, 400);
	setcolor(WHITE);
	for(i = 0.1, x = 0; i < 8; i += 0.1)
	{
		y = 0, x += 0.1;
		y = pfn(x, step);
		setcolor(RED);
		lineto(40 + (int)(x * 40), 400 - (int)(y * 40));
	}
	for(i = 0; i < N; ++i)
	{
		setcolor(YELLOW);
		circle(40 + x0[i] * 40, 400 - y0[i][0] * 40, 2);
	}
	getch();
	closegraph();
}
