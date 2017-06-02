#include <stdio.h>
#include <conio.h>
#include <math.h>

#define EPS 0.000001

float func(float x)
{
	return (x * x - 2 * x - 13);
}

void main()
{
	float A, B, C, C1;
	clrscr();
	printf("Input A: ");
	scanf("%f", &A);
	printf("Input B: ");
	scanf("%f", &B);
	do
	{
		C1 = C;
		C = (func(B) * A - func(A) * B) / (func(B) - func(A));
		if (func(A) * func(C) < 0)
			B = C;
		else
			A = C;
	} while (fabs(C1 - C) > EPS);
	printf("\nSolution %.3f", C);
	getch();
}

