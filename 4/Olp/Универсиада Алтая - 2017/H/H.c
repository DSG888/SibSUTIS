/*
Задача H. Вычислить функцию
	Имя входного файла: number.in
	Имя выходного файла: number.out
	Ограничение по времени: 1 секунда
	Ограничение по памяти: 256 Mb

На экзамене по информатике Саше досталась очень трудная задача: надо вычислить значение функции в заданной точке. Помогите Саше! А функция такая:

Входные данные
	Входной файл содержит единственное целое число n - аргумент функции (0 ≤ n ≤ 60).
Выходные данные
	Выведите в выходной файл значение функции в виде дроби, формат вывода приведен в примере.

Пример входного и выходного файлов
number.in       	number.out       
1					3/2
*/

#include <stdio.h>

typedef struct Fraction{long int num; long int den;} Fraction;

inline Fraction construct_fraction(long int num, long int den)
{
	void norma_fraction(Fraction *frac)
	{
		long int gcd(long int a, long int b)
		{
			if (a == 0)
				return b;
			if (b == 0)
				return a;
			a = a > 0 ? a : -a;
			b = b > 0 ? b : -b;
			while (a != b)
			{
				if (a > b)
					a -= b;
				else
					b -= a;
			}
			return a;
		}
		
		int d = gcd(frac->num, frac->den);
		frac->num /= d;
		frac->den /= d;
		if (frac->den < 0)
		{
			frac->den *= -1;
			frac->num *= -1;
		}
	}
	Fraction result;
	if (den == 0)
	{
		num = 0;
		den = 1;
	}
	result.num = num;
	result.den = den;
	norma_fraction(&result);
	return result;
}

int main()
{
	int myPower(int X, int U)
	{
		int Y = 1, x;
		for (x = 0; x < U; ++x)
			Y = Y * X;
		return Y;
	}
	Fraction fraction_sum(Fraction left, Fraction right)
	{
		Fraction result = construct_fraction(left.num * right.den + left.den * right.num, left.den * right.den);
		return result;
	}
	
	FILE *fp = fopen("number.in", "r");
	int L;
	fscanf(fp, "%d", &L);
	fclose(fp);
	
	Fraction sol = construct_fraction(0, 1);
	long int i = 0;
	for (i = 0; i <= L; ++i)
		sol = fraction_sum(sol, construct_fraction(1, myPower(2, i)));

	fp = fopen("number.out", "w");
	fprintf(fp, "%lu/%lu", sol.num, sol.den);
	return 0;
}
