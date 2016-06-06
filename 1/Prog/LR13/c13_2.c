/*
	На вход программы поступает два целых числа, на экран выводится их наибольший общий делитель (НОД).
*/

#include <stdio.h>

int main()
{
	long int a = 0, b = 0, c = 0, d = 0;

	printf("Введите два целых числа: ");
	scanf("%ld %ld", &a, &b);

	if (a < b)
	{
		c = a;
		a = b;
		b = c;
	}
	if (a % b == 0)
		d = b;
	else
	{
		d = b / 2;
		while ((a % d != 0) || (b % d != 0))
			d = d - 1;
	}
	printf("\tНаибольший общий делитель чисел %ld и %ld равен: %ld\n", a, b, d);

	return 0;
}

