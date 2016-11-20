/*
Реализовать алгоритм вычисления простых чисел в заданном диапазоне при помощи решета Эратосфена.
Программа должна состоять из следующих подпрограмм:
	1. main, функционал: ввод данных, вызов остальных процедур.
	2. eratosfen, функционал: реализация алгоритма, на вход подается диапазон значений и массив, принимающий элементы.
	3. strike, функционал: вычеркивание элементов из входного массива, кратных заданному элементу с номером i.
	4. output, функционал: вывод вычисленных простых чисел.
*/

#include <stdio.h>

void eratosfen(int* arr, const int len, const int n)
{
	int i;
	for (i = 0; i < len; i++)
	{
		arr[i] = i + n;
	}
}

void strike(int* arr, const int len)
{
	int i, j;
	arr[1] = 0;
	for(i = 2; i < len; i++)
	{
		if(arr[i] != 0)
		{
			for(j = i * 2; j < len; j += i)
			{
				arr[j]=0;
			}
		}
	}
}

void output(int MasX[], int M)
{
	int i;
	printf("\t[");
	for (i = 0; i < M; i++)
	{
		MasX[i]?printf("%d,", MasX[i]) : 1;
	}
	printf("]\n");
}

int main()
{
	printf("Введите диапазон значений: ");
	int n = 0, k = 0;
	scanf("%d %d", &n, &k);
	if ((n < 0) || (k < 0) || (n >= k))
	{
		printf("\tДиапазон не оч\n");	
		return 1;
	}
	int Mas[k - n + 1];
	eratosfen(Mas, k - n + 1, n);
	strike(Mas, k - n + 1);
	output(Mas, k - n + 1);
	return 0;
}
