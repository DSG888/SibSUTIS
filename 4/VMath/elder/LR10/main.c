#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>

#define N 4

float func(float x)
{
	return (sqrt(x));
}

float aytk(float x, float x0[], float y0[])
{
	int i, j;
	float *p;

	p = (float*)malloc(sizeof(float) * N);
	for (i = 0; i < N; ++i)
		p[i]=y0[i];
	for (j = N - 1; j >= 0; --j)
		for (i = 0; i < N; ++i)
			p[i] = (p[i] * (x - x0[N - j + i]) - p[i + 1] * (x - x0[i])) / (x0[i] - x0[4 - j + i]);
	return (p[0]);
}

int main()
{
	int i, j, i1, x1, y1;
	float y, x;
	float x0[N], y0[N];
	int gd, gm;

	clrscr();
	gd = 0;
	printf("Введите значение X: \n");
	for(i = 0; i < N; ++i)
   	{
		printf("x%d == ", i);
		scanf("%f", &x0[i]);
		y0[i] = func(x0[i]);
	}
	clrscr();
	initgraph(&gd, &gm, "c:\tc");
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
	for(i = 0; i < 70; ++i)
		lineto(40 + (i * 0.2) * 40, 400 - (int)(func(i * 0.2) * 40));

	moveto(40, 400);
	setcolor(WHITE);
	x = 0;
	for(i = 0; i < 8; ++i)
	{
		y = 0, x++;
		y = aytk(x, x0, y0);
		setcolor(RED);
		lineto(40 + (int)(x * 40), 400 - (int)(y * 400));
	}
	for(i = 0; i < N; ++i)
	{
		setcolor(YELLOW);
		circle(40 + x0[i] * 40, 400 - y0[i] * 40, 2);
	}
	getch();
	closegraph();
	return 0;
}
