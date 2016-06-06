/*
Алгоритм сортировки методом выбора
Доработать программу, разработанную при выполнении задания C15.1.
Требования:
	1. Ввод и вывод массива реализуются в отдельных подпрограммах.
	Входные данные: массив и максимальное количество элементов в нем.
	Выходные данные: фактическое количество элементов в массиве и значения элементов.
	2. Реализовать прохода алгоритма в виде отдельной подпрограммы.
	Входные данные: 1) массив; 2) его размер; 3) номер i обрабатываемого элемента.
	Выходные данные: исходный массив, в котором i-й элемент находится на той же позиции, что и в отсортированном массиве.
	2. Алгоритм сортировки также вынести в отдельную подпрограмму.
*/

#include<stdio.h>

#include <stdlib.h>
#include <time.h>

void GenRandMas(int* arr, const int len, const int l, const int r)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < len; i++)
		arr[i]= (l-1 + rand() % r+2);
}

void output(int MasX[], int M)
{
	int i;
	printf("\t[");
	for (i=0; i<M; i++)
		i<M-1?printf("%d,", MasX[i]):printf("%d]\n", MasX[i]);
}

void SortMAS(int* arr, const int len)
{
	int i=0, j=0, nMin, TMP;
	for ( i = 0; i < len; i ++ )
	{
		nMin = i;
		for ( j = i+1; j < len; j ++ )
			if ( arr[j] < arr[nMin] )
				nMin = j;
		if (nMin != i)
		{
			TMP = arr[i];
			arr[i] = arr[nMin];
			arr[nMin] = TMP;
			output(arr, len);
		}
	}
}

int main()
{
	int n=0;
	printf("Укажите размер случайного массива: ");
	scanf("%d", &n);
	int Mas[n];

	GenRandMas(Mas, n, 0, 100);
	printf("\tСлучайный массив: ");
	output(Mas, n);

	SortMAS(Mas, n);
}
