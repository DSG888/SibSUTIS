//Нелинейные уравнения. Метод бисекции

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 0.001

//plot2d(x * cos (x) , [x,-2*3.14, 2*3.14])

double calc(double x)
{
	return 16-x*x+0.7;
	//return x * cos (x);
}

int bsfind(double a, double b, double c, double eps)
{
	static int i = 1;
	while ((b-a) > eps)
	{
		c = (a + b) / 2;
		if (calc(c) == 0)
			break;
		if (calc(a) * calc(c) < 0)
			b = c;
		else
			a = c;
		
	}
	printf("x%d = %.5lf\n", i++, c);
	return i;
}

int main(int argc, char *argv[])
{
	double a, b, c;
	int Z = 0, Y = 1, i, n;
	
	printf("Интервалы: ");
	scanf("%lf %lf", &a, &b);
	if (a > b)
	{
		double buf = a;
		a = b;
		b = buf;
	}

	n = (fabs(a)+fabs(b)) / 0.01;
	for (i = 0; i < n; i++)
	{
		a = a + 0.1;  

		if (calc(a) > 0)
			Z = 1;
		else
			if (calc(a) < 0 && Z == 1 && Y == 1)
				bsfind(a - 0.1, a, c, EPS)&&(Z = 0);
		if (calc(a) < 0)
			Y = 0;
		else
			if (calc(a) > 0 && Y == 0 && Z == 1)
				bsfind(a - 0.1, a, c, EPS)&&(Y = 1);
	}
	return 0;
}
