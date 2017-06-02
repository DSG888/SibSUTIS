#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

#define N 4

float x[N + 1], y[N + 1];
float h[N];
float d[N], M[N];
float C[N][N];
float Cd[N][N + 1];
float t, x0, p, ss = 0;
int i, j, k;
int i1, xx, yy;
int gd = 0, gm;

float s(float p)
{
	float k1, k2, k3, k4;

	for (j = 0; j < N; ++j)
		if ((p >= x[j]) && (p < x[j + 1]))
			i = j;

	k1 = M[i - 1] * (x[i + 1] - p) * (x[i + 1] - p) * (x[i + 1] - p) / (6 * h[i]);
	k2 = M[i] * (p - x[i]) * (p - x[i]) * (p - x[i]) / (6 * h[i]);
	k3 = (y[i] - M[i - 1] * h[i] * h[i] / 6) * (x[i + 1] - p) / h[i];
	k4 = (y[i + 1] - M[i] * h[i] * h[i] / 6) * (p - x[i]) / h[i];

	return (k1 + k2 + k3 + k4);
}

void main()
{
	clrscr();
	printf("Введите X0: ");
	scanf("%f", &x0);

	for (i = 0; i <= N; ++i)
	{
   		printf("X%d> ", i);
   		scanf("%f", &x[i]);
   	}

	for (i = 0; i <= N; ++i)
	{
   		printf("Y%d> ", i);
	   	scanf("%f", &y[i]);
	}

	/* Расчет вектора h */
	for(i = 0; i < N; ++i)
		h[i] = x[i + 1] - x[i];
	for(i = 0; i < N; ++i)
		printf("h = %.3f\n", h[i]);

	/* Расчет матрицы C */
	for (i = 0; i < N - 1; ++i)
	   	for (j = 0; j < N - 1; ++j)
		{
			if (i == j)
				C[i][j] = (h[i] + h[i + 1]) / 3;
          	if (j == i + 1)
				C[i][j] = h[i + 1] / 6;
          	if (j == i - 1)
				C[i][j] = h[i] / 6;
          	if (abs(i - j) >= 2)
				C[i][j] = 0;
      	}

	/* Расчет вектора d */
	for (i = 0; i < N - 1; ++i)
		d[i] = (y[i + 2] - y[i + 1]) / h[i + 1] - (y[i + 1] - y[i]) / h[i];

	/* Вывод вектора d */
	printf("Вектор d:\n");
   	for (i = 0; i < N - 1; ++i)
		printf("%.3f\n", d[i]);

	/* Вывод матрицы C */
	printf("\nМатрица C:\n");
	for (i = 0; i < N - 1; ++i)
	{
		for (j = 0; j < N - 1; ++j)
			printf("%.3f  ", C[i][j]);
		printf("\n");
   	}
   	printf("\n");

	/* Цикл для образования матрицы Cd */
	for (i = 0; i < N - 1; ++i)
		for (j = 0; j < N; ++j)
			if (j <= N - 2)
				Cd[i][j] = C[i][j];
			else
				Cd[i][j] = d[i];

	/*for (i = 0; i < N - 1; ++i)
		Cd[i][N - 1] = d[i];*/
	/* Прямой ход метода Гаусса */
	for (j = 0; j < N - 2; ++j)
		for (i = j + 1; i < N - 1; ++i)
		{
			t = -Cd[i][j] / Cd[j][j];
			if (t)
				for (k = 0; k < N + 1; ++k)
					Cd[i][k] = Cd[i][k] + t * Cd[j][k];
		}
	/* Обратный ход */
	for (t = 0, i = N - 2; i >= 0; --i)
	{
		M[i] = Cd[i][N - 1] / Cd[i][i] - t; t = 0;
		if (i > 0)
			for (j = N - 2; j >= i; --j)
				t = t + (Cd[i - 1][j] * M[j]) / Cd[i - 1][i - 1];
	}
   	/* Вывод вектора M */
	printf("\nВектор M:\n");
	for (i = 0; i < N - 1; ++i)
   		printf("%.3f\n", M[i]);

   	printf("\n");
	/* Расчет множества значений S(p), где "p" проходит от x[0] до x[n] с шагом t */
	/*t = (x[N] - x[0]) / (N1 + 1);
   	p = x[0];
   	l = 0;
	while(p <= x[N])
	{
      		x1[l] = p;
      		y1[l] = s(p);
      		l++;
      		p += t;
	}*/
	printf("s(x0)=%.4f\n", s(x0));
	getch();
	clrscr();
	initgraph(&gd, &gm, "..");
	cleardevice();

	outtextxy(30, 40, "Y");
	outtextxy(600, 403, "X");

	line(40, 40, 40, 400);
	line(40, 400, 600, 400);

	for (xx = 40, i = 0; i < 8; ++i)
	{
		xx += 40;
		line(xx, 398, xx, 402);
	}
	for (yy = 400, i = 0; i < N; ++i)
	{
		yy -= 40;
		line(38, yy, 42, yy);
	}

	moveto(40 + x[0] * 40, 400 - y[i] * 40);
	setcolor(BLUE);
	for (i = 0; i <= N; ++i)
		lineto(40 + x[i] * 40, 400 - y[i] * 40);

	moveto(40 + x[0] * 40, 400 - s(x[0]) * 40);
	setcolor(WHITE);
	getch();
	for (ss = x[0]; ss < x[N]; ss += 0.2)
	{
		setcolor(RED);
		lineto(40 + ss * 40, 400 - (s(ss) * 40));
	}
	for (i = 0; i <= N; ++i)
	{
		setcolor(YELLOW);
		circle(40 + x[i] * 40, 400 - y[i] * 40, 2);
	}
	setcolor(GREEN);
	circle(40 + x0 * 40, 400 - s(x0) * 40, 2);
	getch();
	closegraph();
}
