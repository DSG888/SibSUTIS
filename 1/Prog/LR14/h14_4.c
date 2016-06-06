/*
Дана последовательность чисел а 1 , а 2 , ..., а n . Указать наименьшую длину числовой оси, содержащую все эти числа. Например: последовательность 6, 9, 18, 3, 20, 8, 15, ответ: [3, 20].
*/

#include<stdio.h>

int main()
{
	int a=0;
	printf("Введите количество элементов: ");
	scanf("%d", &a);
	int Mas[a], i;
	for (i=0; i<a; i++)
	{
		printf("Введите %d элемент: ", i+1);
		scanf("%d", &Mas[i]);
	}

	int nmax=0, nmin=0, max=Mas[0], min=Mas[0];
	for (i=0; i<a; i++)
	{
		if (min > Mas[i])
		{
			nmin = i;
			min = Mas[i];
		}
		if (max < Mas[i])
		{
			nmax = i;
			max = Mas[i];
		}
	}
	printf("\tПромежуток: [%d,%d]\n", Mas[nmin], Mas[nmax]);
	return 0;
}


