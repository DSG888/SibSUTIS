//Нелинейные уравнения. Метод Ньютона

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 0.0001

double calc(double x)
{
	return 16-x*x+0.7;
}

double derivative(double x)
{
	return -2*x;
}

int main(int argc, char *argv[])
{
	double x = 0.001, x0;
	int i = 1;
	do
	{
		x0 = x;
		x = x0 - calc(x) / derivative(x);
	}
	while (EPS < fabs(x0 - x));
	printf("x1 = %.5lf\n", x);
	if (EPS > calc(-x))
		printf("x2 = %.5lf\n", -x);
}
