#include <stdio.h>
#include <stdlib.h>

char *MStr;

double charToDigit(int i1, int i2)
{
	int power(int x, int n)
	{
		if(n == 0)
			return 1;
		if(n < 0)
			return 1 / (x * power (1 / x, n + 1));
		return x * power(x, n - 1);
	}

	double Result = 0, doubles = 0;
	int i, d;
	for (i = i1; i <= i2; i++)
	{
		if (MStr[i] != '.')
			Result = (Result + (MStr[i] - '0')) * 10;
		else
			break;
	}
	Result = Result / 10;
	d=i;
	for (i = i + 1; i <= i2; i++)
		if (MStr[i] != '.')
			Result = Result + (doubles + (MStr[i] - '0')) / power(10, i - d);
		else
			break;
	return Result;
}


double MyEval(int Start, int End)
{
	int i = Start, OtkSKa, ZakSKa, OtkSKb, ZakSKb, Tmp = 0;

	if ((MStr[Start] == '(') && (MStr[End] == ')'))
	{
		OtkSKa = 1;
		ZakSKa = 0;
		i++;
		while(!(OtkSKa == ZakSKa))
		{
			if (MStr[i] == '(')
				OtkSKa++;
			if (MStr[i] == ')')
				ZakSKa++;
			i++;
		}
		i--;
		if (i == End)
			return MyEval(Start + 1, End - 1);
	}

	for (i = Start; i <= End; i++)
	{
		switch (MStr[i])
		{
			case '+':
				return MyEval(Start, (i - 1)) + MyEval((i + 1), End);
			case '-':
				if (i > Tmp)
					Tmp = i;
				break;
			case '*': if (Tmp == 0)
					Tmp = i;
				break;
			case '/':
				if ((Tmp == 0) || (MStr[Tmp] == '/'))
					Tmp = i;
				break;
			case '(':
				OtkSKb = 1;
				ZakSKb = 0;
				i++;
				while(!(OtkSKb == ZakSKb))
				{
					if (MStr[i] == '(')
						OtkSKb++;
					if (MStr[i] == ')')
						ZakSKb++;
					i++;
				}
				i--;
				break;
		}
	}
	if (Tmp > 0)
	{
		switch(MStr[Tmp])
		{
			case '-': return MyEval(Start, Tmp - 1) - MyEval(Tmp + 1, End);
			case '*': return MyEval(Start, Tmp - 1) * MyEval(Tmp + 1, End);
			case '/': return MyEval(Start, Tmp - 1) / MyEval(Tmp + 1, End);
		}
	}
	return charToDigit(Start, End);
}

int main(int argc, char **argv)
{
	int chcmp (char ch, char *list)
	{
		int i;
		for (i = 0; list[i] != '\0'; ++i)
		{
			if (ch == list[i])
				return 1;
		}
		return 0;
	}
	
	if (argc != 2)
		return 1;
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

	double result = MyEval(0, z - 1);
	printf("\t\t%s = %lf\n", MStr, result);
	return 0;
}
