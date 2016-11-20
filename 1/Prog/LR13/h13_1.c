/*
Задача:
	На вход программы поступает вещественное x в десятичной системе счисления. Необходимо вывести на экран его двоичное представление с точностью до n знаков после запятой (n также задается с клавиатуры).
Пример:
	x = 87, Вывод на экран: 1010111,10010001
*/

#include<stdio.h>

int main()
{
	double a = 0 , Fractional = 0, FractionalBin = 0, Denominator = 0.1;
	int Integer = 0, IntegerBin = 0, Correctness = 0, Factor = 1, b = 0, pResult = 0, i = 0;

	printf("Введите вещественное число [float]: ");
	scanf("%lf", &a);
	printf("Введите точность [int]: ");
	scanf("%d", &Correctness);

	Integer = a;
	while (Integer > 0)
	{
		b = Integer % 2;
		IntegerBin = IntegerBin + b * Factor;
		Factor = Factor * 10;
		Integer = Integer / 2;
	}
	Factor = 1;

	Integer = a;
	Fractional = a - Integer;
	for (i = 0; i < Correctness; i++)
	{
		Fractional = Fractional * 2;
		Integer = Fractional;
		FractionalBin = FractionalBin + Integer * Denominator;
		pResult = pResult + Integer * Factor;
		Factor *= 10;
		Denominator /= 10;
		if (Fractional > 1)
			Fractional--;
	}
	printf("\tДвоичное представление вещественного числа %lf: %lf\n", a, IntegerBin + FractionalBin);
	return 0;
}
