#include <stdio.h>
#include <conio.h>

#define EPS 0.000001

float func(float x)
{
	return (x * x - 2 * x - 13);
}

int main()
{
	float A, B, C, fA, fB, fC, eps;
	clrscr();
	printf("Input A: ");
	scanf("%f", &A);
	printf("Input B: ");
	scanf("%f", &B);
	do
	{
		C = (A + B) / 2;
		fA = func(A);
		fB = func(B);
		fC = func(C);
		if (fC == 0)
			break;
		eps = (B - A) / 2;
		if (fA * fC < 0)
			B = C;
		else
			A = C;
	} while (eps > EPS);
	C = (A + B) / 2;
	printf("\nSolution %.3f", C);
	getch();
	return 0;
}
