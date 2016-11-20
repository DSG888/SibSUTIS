/*
Алгоритм сортировки методом вставки
	Доработать программу H16.2 так, чтобы в режиме отладки помимо содержимого массива отображалась информация об абсолютном и относительном количестве инверсий для данного состояния массива.
	Отладочный вывод реализовать в виде подпрограммы. На вход поступает массив и количество элементов в нем. Выходных данных не предусмотрено.
*/

#include<stdio.h>

#include <stdlib.h>
#include <time.h>

void GenRandMas(int* arr, const int len, const int l, const int r)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < len; i++)
		arr[i]= (l - 1 + rand() % r + 2);
}

void KMUoutput(int MasX[], int M)
{
	int i, j, n = 0;
	double maxi = 0, d = 1;

	for (i = 0; i < M - 1; i++)
	{
		maxi = maxi + M - i - 1;
		for (j = i; j < M; j++)
		{
			if (MasX[i] > MasX[j])
				n++;
		}
	}
	d = d * (n / maxi);

	printf("\t[");
	for (i = 0; i < M; i++)
		i < M - 1 ? printf("%d,", MasX[i]) : printf("%d] ", MasX[i]);
	printf("(abs.inv)=%d; (rel.inv) = %.4lf\n", n, d);
}

void SortMV(int* arr, const int len)
{
	int i = 0, j = 0, tmp = 0;
	for (i = 1; i < len; i++)
	{
		tmp = arr[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (arr[j] < tmp)
				break;
			arr[j + 1] = arr[j];
			arr[j] = tmp;
			KMUoutput(arr, len);
		}
	}
}

int main()
{
	int n=0;
	printf("Укажите размер случайного массива: ");
	scanf("%d", &n);
	int Mas[n];

	srand(time(NULL));
	printf("\tСлучайный массив: ");
	GenRandMas(Mas, n, 0, 100);
	KMUoutput(Mas, n);
	SortMV(Mas, n);
}
