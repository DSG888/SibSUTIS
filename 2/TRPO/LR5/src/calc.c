#include <math.h>
#include <float.h>
#include <stdio.h>
#include "consts.h"

int SolveEquation (double a, double b, double c, double *x1, double *x2)
/*
	Функция нахождения корней квадратного уравнения
*/
{
	*x1 = 0;
	*x2 = 0;
	if (IsZero (a))
		if (IsZero (b))					// Линейный коэффициент
			if (IsZero (c))				// Константа
				return ENDLESS_ROOTS;	// Уравнение 0=0
			else
				return NO_ROOT;			// Уравнение c=0, c!=0
		else
		{
			*x1 = -c / b;				// Уравнение bx+c=0, b!=0
			return ONE_ROOT;
		}
	else
	{
		// Квадратное уравнение
		double d = b*b - (4*a*c);
		
		if (IsZero (d))
		{
			*x1 = -b / (2*a);
			return ONE_ROOT;
		}
		
		if (IsMoreZero (d))
		{
			double sqrt_d;
			sqrt_d = sqrt (d);
			*x1 = (-b - sqrt_d) / (2*a);
			*x2 = (-b + sqrt_d) / (2*a);
			return TWO_ROOTS;
		}
		
	//	if (IsLessZero (d))
		return NO_ROOT;
	}
//	return -1;						// Заглушка
}

void fCalc(double a, double b, double c, char *MAS)
{
	double x1, x2;
	printf("   Входные данные: А=%lf; B=%lf; C=%lf;\n", a, b, c);	
	
	switch (SolveEquation (a, b, c, &x1, &x2))
	{
		case NO_ROOT:
			sprintf (MAS, "\tУравнение не имеет корней\n");
			break;
		case ONE_ROOT:
			sprintf (MAS, "\tНайден один корень: x = %lf\n", x1);
			break;
		case TWO_ROOTS:
			sprintf (MAS, "\tНайдены два корня: x1 = %lf и x2 = %lf\n", x1, x2);
			break;
		case ENDLESS_ROOTS:
			sprintf (MAS, "\tУравнение имеет бесконечное множество корней\n");
			break;
	}
}
