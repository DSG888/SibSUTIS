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

float lagr(float x, float x0[])
{
	int i, j;
	float y = 0, k;

	for (i = 0; i < N; ++i)
	{
		k = 1;
		for (j = 0; j < N; ++j)
			if (i != j)
				k *= (x - x0[j]) / (x0[i] - x0[j]);
		y += func(x0[i]) * k;
	}
	return (y);
}

int main()
{
	int j, i1, x1, y1;
	float y, x, i;
	float x0[N], y0[N];
	int gd, gm;

	clrscr();
	printf ("Введите значение X: \n");
	for (i=0;i<N;i++)
	{
		printf("x%d == ", i);
		scanf("%f", &x0[i]);
		y0[i] = func(x0[i]);
	}
	clrscr();
	gd = 0;
	initgraph(&gd, &gm, "d:\tc");
	cleardevice();

	outtextxy(30, 40, "Y");
	outtextxy(600, 400, "X");

	line(40, 40, 40, 400);
	line(40, 400, 600, 400);

	for (x1 = 40, i = 0; i < 8; ++i)
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
	for(i = 0; i < 8; i += 0.1)
	{
		y = 0, x += 0.1;
		y = lagr(x, x0);
		setcolor(RED);
		lineto(40 + (int)(x * 40), 400 - (int)(y * 40));
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
