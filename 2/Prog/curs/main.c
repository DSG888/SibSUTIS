#include <stdio.h>
#include <stdlib.h>
#include "cmdcalc.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	char *MStr;
	MStr = malloc(sizeof(char) * 9000);
	int z = 0, i, j, a = 0;
	for (i = 0; argv[1][i] != '\0'; i++)
	{
		if (argv[1][i] == ' ')
			continue;
		if (chcmp(argv[1][i], "()+-*/,.0123456789"))
		{	
			if (argv[1][i] != ',')
				MStr[z] = argv[1][i];
			else
				MStr[z] = '.';
			z++;
			if (argv[1][i] == '(')
				a++;
			else 
				if (argv[1][i] == ')' && --a < 0)
				{
					printf("Ошибка ввода. Скобка закрыта до открытия\n");
					return 1;
				}
		}
		else
		{
			printf("Ошибка ввода. Запрещенный символ\n");
			return 1;
		}
	}
	if (a)
	{
		printf("Ошибка ввода. Нарушен баланс скобок\n");
		return 1;
	}
	for(i = 0; MStr[i] != '\0'; i++)
	{
		if (( (MStr[i] == '.')  ) && ((0 > i - 1) || ('\0' == MStr[i + 1])))
		{
			printf("Ошибка ввода. Вещественная часть не введена\n");
			return 1;
		}
		if (chcmp(MStr[i], "+-*/") && ( (0 >= i) || ('\0' == MStr[i + 1]) || ( (MStr[i - 1] == '(')) || MStr[i + 1] == ')' || ((0 < i) && chcmp(MStr[i - 1], "+-*/") || chcmp(MStr[i + 1], "+-*/"))))
		{
			printf("Ошибка ввода. Ошибка расстановки знаков\n");
			return 1;
		}
		if (MStr[i] == '.')
		{
			if (chcmp(MStr[i + 1], "()") || chcmp(MStr[i - 1], "()"))
			{
				printf("Ошибка ввода. Точка до или после скобки\n");
				return 1;
			}
			for (j = i + 1; MStr[j] != '\0'; ++j)
			{
				if (chcmp(MStr[j], "+-*/"))
					break;
				else
				{
					if (MStr[j] == '.')
					{
						printf("Ошибка ввода. Более одной точки в одном числе\n");
						return 1;
					}
				}
			}
		}
		if ((MStr[i] == '(') && (0 < i))
		{
			if (0 == chcmp(MStr[i - 1], "(+-*/"))
			{
				printf("Ошибка ввода. Нет знака до скобки\n");
				return 1;
			}
			if (')' == MStr[i + 1])
			{
				printf("Ошибка ввода. () не допускается\n");
				return 1;
			}
		}		
		if ((MStr[i] == ')') && (MStr[i + 1] != '\0'))
		{
			if (0 == chcmp(MStr[i + 1], ")+-*/"))
			{
				printf("Ошибка ввода. Нет знака после скобки\n");
				return 1;
			}
		}
	}

	double result = MyEval(MStr, 0, z - 1);
	printf("\t\t%s = %lf\n", MStr, result);
	return 0;
}
