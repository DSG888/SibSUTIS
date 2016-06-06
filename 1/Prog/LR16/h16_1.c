/*
Разработать подпрограмму, вычисляющую количество инверсий в заданном массиве.
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

/*
void output(int MasX[], int M)
{
	int i;
	printf("\t[");
	for (i=0; i<M; i++)
		i<M-1?printf("%d,", MasX[i]):printf("%d]\n", MasX[i]);
}
*/

void KMUoutput(int MasX[], int M)
{
	int i,j, n=0;
	double maxi=0, d=1;

	for (i=0; i<M-1; i++)
	{
		maxi = maxi + M - i - 1;
		for (j=i; j<M; j++)
			if (MasX[i]>MasX[j])
				n++;
	}
	d = d * (n / maxi);

	printf("\t[");
	for (i=0; i<M; i++)
		i<M-1?printf("%d,", MasX[i]):printf("%d] ", MasX[i]);
	printf("(abs.inv)=%d; (rel.inv) = %.4lf\n", n,d);
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

	GenRandMas(Mas, n, 0, 100);
	printf("\tСлучайный массив: ");
	KMUoutput(Mas, n);

	SortMAS(Mas, n);
}
