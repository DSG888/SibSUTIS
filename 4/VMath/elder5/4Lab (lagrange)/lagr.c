#include <stdio.h>

double f(double x)
{
	return  x*x*x + 3*x*x + 3*x + 1; 
}

int main()
{
	const int size = 4;
	int i, j;
	double x[] = {2, 3, 4, 5};
	double y[] = {-1, 2, 3, 1};
	double inter = 3.5;

	/*for (int i = 0; i < size; i++)
	{
		x[i] = i; 
		y[i] = f(x[i]);
	} */

	printf("x\t\ty\n");
	for (i = 0; i < size; i++)
	{
		printf("%3.2lf\t%10.2lf\n", x[i], y[i]);
	}
	double lagrange = 0;
	double bas;

	for (i = 0; i < size; i++)
	{
		bas = 1;
		for (j = 0; j < size; j++)
		{
			if (j == i) continue;
			bas = bas * ((inter - x[j])/(x[i] - x[j]));		
		}
		lagrange = lagrange + (bas * y[i]);
	}
	printf ("\nx(%lf) = %lf\n", inter, lagrange);

	return 0;
}
