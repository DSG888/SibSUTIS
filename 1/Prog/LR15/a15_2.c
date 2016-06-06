/*
Доработать программу H15.3 так, чтобы в режиме отладки помимо содержимого массива отображалась информация об абсолютном и относительном количестве инверсий для данного состояния массива.
*/

#include<stdio.h>

#include <stdlib.h>
#include <time.h>

void output(int MasX[], int M)
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
		MasX[i]?printf("%d,", MasX[i]):1;
	printf("] (abs.inv)=%d; (rel.inv) = %.4lf\n", n,d);
}

int main()
{
	int n=0, i=0, j=0, tmp=0, l=0, r=100;
	printf("Укажите размер случайного массива: ");
	scanf("%d", &n);
	int Mas[n];

	srand(time(NULL));
	printf("\tСлучайный массив: [");
	for(i=0; i < n; i++)
	{
		Mas[i]= (l-1 + rand() % r+2);
		i<n-1?printf("%d,", Mas[i]):printf("%d]\n", Mas[i]);
	}

	for(i = 0 ; i < n - 1; i++) 
		for(j = 0 ; j < n - i - 1 ; j++)
			if(Mas[j] > Mas[j+1])
			{
				tmp = Mas[j]; Mas[j] = Mas[j+1] ; Mas[j+1] = tmp;
				output(Mas, n);
			}

}
