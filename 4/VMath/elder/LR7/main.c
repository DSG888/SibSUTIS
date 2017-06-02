#include <stdio.h>
#include <conio.h>
#include <math.h>

#define EPS 0.000001

int mas[3];

/* Уравнение второго порядка */
float func(float x)
{
	return (mas[0] * x * x + mas[1] * x + mas[2]);
}

/* Производная от уравнения второго порядка */
float d_func(float x)
{
	return (2 * mas[0] * x + mas[1]);
}

void main()
{
	float A, B, C, C1;
	clrscr();
	printf("Input coefficients: ");
	scanf("%d%d%d", &mas[0], &mas[1], &mas[2]);
	if (mas[0] != 0 && mas[1] != 0 && mas[2] != 0)
		printf("Equation: (%d)*x^2+(%d)*x+(%d)\n", mas[0], mas[1], mas[2]);
	else
		if (mas[0] == 0 && mas[1] != 0 && mas[2] != 0)
			printf ("Equation: (%d)*x+(%d)\n", mas[1], mas[2]);
		else
			if (mas[0] == 0 && mas[1] == 0 && mas[2] == 0)
			{
				printf("Equation: 0\n");
				goto end;
			}
			else
				if (mas[0] != 0 && mas[1] == 0 && mas[2] != 0)
					printf("Equation: (%d)*x^2+(%d)\n", mas[0], mas[2]);
				else
					if (mas[0] != 0 && mas[1] != 0 && mas[2] == 0)
						printf("Equation: (%d)*x^2+(%d)*x\n", mas[0], mas[1]);
	printf("Input A: ");
	scanf("%f", &A);
	printf("Input B: ");
	scanf("%f", &B);
	do
	{
		C1 = C;
		C = (C1 - func(C1) / d_func(C1));
	} while (fabs(C1 - C) > EPS);

end:
	if (C < A || C > B)
		printf("There is no solution.");
	else
		printf("\nSolution %.3f", C);
	getch();
}
