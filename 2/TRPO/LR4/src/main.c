//	gcc main.c -lm

#include <stdio.h>
#include "equation.h"

#define NO_ROOT       0
#define ONE_ROOT      1
#define TWO_ROOTS     2
#define ENDLESS_ROOTS 3

#define IsZero(x)     (fabs(x) <= DBL_EPSILON)
#define IsMoreZero(x) (x > DBL_EPSILON)
#define IsLessZero(x) (x < -DBL_EPSILON)


int main (int argc, char *argv[])
{
	double a, b, c, x1, x2;
	
	printf ("Введите коэффициенты квадратичного уравнения (a, b, c): ");
	scanf ("%lf %lf %lf", &a, &b, &c);
	
	switch (SolveEquation (a, b, c, &x1, &x2))
	{
		case NO_ROOT:
			printf ("\tУравнение не имеет корней\n");
			break;
		case ONE_ROOT:
			printf ("\tНайден один корень: x = %lf\n", x1);
			break;
		case TWO_ROOTS:
			printf ("\tНайдены два корня: x1 = %lf и x2 = %lf\n", x1, x2);
			break;
		case ENDLESS_ROOTS:
			printf ("\nУравнение имеет бесконечное множество корней\n");
			break;
	}
	return 0;
}
