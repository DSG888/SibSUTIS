/*
На вход программы поступает два целых числа, на экран выводится их наибольший общий делитель (НОД).

Замечания:
1. Для решения задачи использовать алгоритм Евклида поиска НОД на базе вычитания (согласно лекционному занятию "Алгоритмы на базе циклических конструкций").
2. Сравнить время работы программ C13.2, C13.3, H13.2 и H13.3 для чисел 12390757417 и 12472821941 - (12390757417, 12472821941) = 3533. Для сравнения использовать команду time:
time ./h13_3 где h13_3 – имя исполняемого файла программы.
*/

#include<stdio.h>

int main()
{
	long int a = 0, b = 0, c = 0, d = 0;
	printf("Введите два целых числа: ");
	scanf("%ld %ld", &a, &b);

	if (a > b)
	{
		c = a;
		a = b;
		b = c;
	}

	while ((b % a) != 0)
	{
		d = b % a;
		b = a;
		a = d;
	}
	printf("\tНаибольший общий делитель: %ld\n", a);
	return 0;
}
