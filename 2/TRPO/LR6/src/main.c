//	gcc main.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

int main (int argc, char *argv[])
{
	double a, b, c;
	char *Out = (char *)malloc(800 * sizeof(*Out));
	
	if (argc == 4)
	{
		a = atof(argv[1]);
		b = atof(argv[2]);
		c = atof(argv[3]);

		//Проверка данных
//		if ((a==0)&&(argv[1][0]!='0'))
		if ((a==0)&&(strcmp(argv[1], "0")) || (b==0)&&(strcmp(argv[2], "0")) || (c==0)&&(strcmp(argv[3], "0")))
		{
			printf("\tОшибка ввода данных\n");
			return 1;
		}
	}
	else
	{
		printf ("Введите коэффициенты квадратичного уравнения (a, b, c): ");
		scanf ("%lf %lf %lf", &a, &b, &c);
	}

	fCalc(a, b, c, Out);
	printf("%s", Out);
	free(Out);
	return 0;
}
