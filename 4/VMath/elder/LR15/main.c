/* Численные методы решения ДУ (метод Эйлера, Рунге-Кутта) */
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define H 0.2

double f(double x, double y)
{
	return ((y - x * x) / x);
}

double ayler(double x, double yy)
{
	return (yy + H * f(x, yy));
}

double runge2pr(double x, double y)
{
	double yy, y1;
	yy = y + H * f(x, y);
	y1 = y + H * (f(x, y) + f(x + H, yy)) / 2;
	return y1;
}

double runge2vr(double x, double y)
{
	double yy, y1;
	yy = y + H / 2 * f(x, y);
	y1 = y + H * f(x + H / 2, yy);
	return y1;
}

double runge4(double x, double y)
{
	double k1, k2, k3, k4, y1;
	k1=f(x, y);
	k2=f(x + H / 2, y + H / 2 * k1);
	k3=f(x + H / 2, y + H / 2 * k2);
	k4=f(x + H, y + H * k3);

	y1 = y + H / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
	return y1;
}

void main()
{
	double x = 1, y = 2;
	clrscr();
	printf("Результат после метода Эйлера.\n");
	while (x < 3)
	{
		y = ayler(x, y);
		printf("y(%.2f) = %.10f\n", x + H, y);
		x += H;
	}
	x = 1, y = 2;
	printf("\nРезультат после метода Рунге-Кутта 2-го порядка с усреднением по производной.\n");
	while (x < 3)
	{
		y = runge2pr(x, y);
		printf("y(%.2f) = %.10f\n", x + H, y);
		x += H;
	}
	x = 1, y = 2;
	printf("\nРезультат после метода Рунге-Кутта 2-го порядка с усреднением по времени.\n");
	while (x < 3)
	{
		y = runge2vr(x, y);
		printf("y(%.2f) = %.10f\n", x + H, y);
		x += H;
	}
	x = 1, y = 2;
	printf("\nРезультат после метода Рунге-Кутта 4-го порядка.\n");
	while(x < 3)
	{
		y = runge4(x, y);
		printf("y(%.2f) = %.10f\n", x + H, y);
		x += H;
	}
	getch();
}
