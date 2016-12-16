#include "cmdcalc.h"

double charToDigit(char *str, int i1, int i2)
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
		if (str[i] != '.')
			Result = (Result + (str[i] - '0')) * 10;
		else
			break;
	}
	Result = Result / 10;
	d=i;
	for (i = i + 1; i <= i2; i++)
		if (str[i] != '.')
			Result = Result + (doubles + (str[i] - '0')) / power(10, i - d);
		else
			break;
	return Result;
}


double MyEval(char *str, int Start, int End)
{
	int i = Start, OtkSKa, ZakSKa, OtkSKb, ZakSKb, Tmp = 0;

	if ((str[Start] == '(') && (str[End] == ')'))
	{
		OtkSKa = 1;
		ZakSKa = 0;
		i++;
		while(!(OtkSKa == ZakSKa))
		{
			if (str[i] == '(')
				OtkSKa++;
			if (str[i] == ')')
				ZakSKa++;
			i++;
		}
		i--;
		if (i == End)
			return MyEval(str, Start + 1, End - 1);
	}

	for (i = Start; i <= End; i++)
	{
		switch (str[i])
		{
			case '+':
				return MyEval(str, Start, (i - 1)) + MyEval(str, (i + 1), End);
			case '-':
				if (i > Tmp)
					Tmp = i;
				break;
			case '*': if (Tmp == 0)
					Tmp = i;
				break;
			case '/':
				if ((Tmp == 0) || (str[Tmp] == '/'))
					Tmp = i;
				break;
			case '(':
				OtkSKb = 1;
				ZakSKb = 0;
				i++;
				while(!(OtkSKb == ZakSKb))
				{
					if (str[i] == '(')
						OtkSKb++;
					if (str[i] == ')')
						ZakSKb++;
					i++;
				}
				i--;
				break;
		}
	}
	if (Tmp > 0)
	{
		switch(str[Tmp])
		{
			case '-': return MyEval(str, Start, Tmp - 1) - MyEval(str, Tmp + 1, End);
			case '*': return MyEval(str, Start, Tmp - 1) * MyEval(str, Tmp + 1, End);
			case '/': return MyEval(str, Start, Tmp - 1) / MyEval(str, Tmp + 1, End);
		}
	}
	return charToDigit(str, Start, End);
}

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
