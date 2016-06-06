/*
Разработать программу, которая принимает на вход массив целых чисел. Ввод массива реализовать аналогично С14.1. Результатом работы программы является исходный массив, в котором максимальный и минимальный элементы переставлены.
Например:
	вход: 10 4 15 26 7 3 19 8
	выход: 10 4 15 3 7 26 19 8
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main()
{
	srand(time(NULL));
	int a = 0, n=0, k=100;
	printf("Введите число элементов массива (1-100): ");
	scanf("%d",&a);
	if ((a > 100)||(a < 1))
	{
		printf("Число нужно от 1-100\n");
		exit(1);
	}
	int Mas[a];
	int minz=INT_MAX, maxz=INT_MIN, nmin, nmax, i=0;
	printf("\tСлучайный массив: [");
	for(i=0; i < a; i++)
	{
		Mas[i]= (n-1 + rand() % k+2);
		printf("%d,", Mas[i]);
		if (Mas[i] < minz)
		{
			minz = Mas[i];
			nmin = i;
		}

		if (Mas[i] > maxz)
		{
			maxz = Mas[i];
			nmax = i;
		}
	}
	printf("]\n");
	printf("\tМинимальное значение: [%d] = %d\n\tМаксимальное значение: [%d] = %d\n", nmin,minz,nmax,maxz);

	//ШАЙТАН//
	Mas[nmax] = Mas[nmax] ^ Mas[nmin];
	Mas[nmin] = Mas[nmin] ^ Mas[nmax];
	Mas[nmax] = Mas[nmax] ^ Mas[nmin];

	printf("\tНовый массив: [");
    for (i=0; i < a; i++)
    	printf("%d,", Mas[i]);
	printf("]\n");
	return 0;
}

