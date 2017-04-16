//Нелинейные уравнения. Метод хорд

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 0.001

//plot2d(x * cos (x) , [x,-2*3.14, 2*3.14])

double calc(double x)
{
	//return 16-x*x+0.7;
	return x * cos (x);
}

int Line(double a, double b, double eps)
{
	static int i = 1;
	while (fabs(b - a) > eps)
	{
		a = b - (b - a) * calc(b) / (calc(b) - calc(a));
		b = a - (a - b) * calc(a) / (calc(a) - calc(b));
	}
	printf("x%d = %.5lf\n", i++, b);
	return i;
}

int main(int argc, char *argv[])
{
	double a, b;
	int i, n, Z = 0, Y = 1;
	
	printf("Интервалы: ");
	scanf("%lf %lf", &a, &b);
	if (a > b)
	{
		double buf = a;
		a = b;
		b = buf;
	}

	n = (fabs(a)+fabs(b))/0.01;
	for (i = 0; i < n; i++)
	{
		a = a + 0.1;
		if (0 < calc(a))
			Z = 1;
		else
			if (calc(a) < 0 && Z == 1 && Y == 1)
			 	Line(a - 0.1, a, EPS)&&(Z = 0);
		if (0 > calc(a))
			Y = 0;
		else
			if (calc(a) > 0 && Y == 0 && Z == 1)
				Line(a - 0.1, a, EPS)&&(Y = 1);
	}
	return 0;
}
