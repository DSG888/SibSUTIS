/*
Реализовать один из рассмотренных линейных алгоритмов вычисления простых чисел в заданном диапазоне.
Программа должна состоять из следующих подпрограмм:
	1. main, функционал: ввод данных, вызов остальных процедур.
	2. prime_linear, функционал: реализация алгоритма, на вход подается диапазон значений и массив, принимающий элементы.
	3. strike, функционал: вычеркивание элементов из входного массива, кратных заданному элементу с номером i.
	4. output, функционал: вывод вычисленных простых чисел.
*/

#include <stdio.h>

void eratosfen(int* arr, const int len, const int n)
{
	int i;
	for (i=0; i<len; i++)
		arr[i] = i+n;
}

void prime_linear(int* arr, const int len)
{
	int i;
	for(i=0; i<len; i++)
		arr[i] = strike(arr[i])*arr[i];
}

int strike(int n)
{
	int d;
	if (n==1)
		return 0;				// 1 - не простое число
	for (d=2; d*d <= n; d++)	// перебираем возможные делители от 2 до sqrt(n)
		if ((n % d) == 0)
			return 0;			// если разделилось нацело, то составное
	return 1;					// если нет нетривиальных делителей, то простое
}

void output(int MasX[], int M)
{
	int i;
	printf("\t[");
	for (i=0; i<M; i++)
		MasX[i]?printf("%d,", MasX[i]):1;
	printf("]\n");
}

int main()
{
	printf("Введите диапазон значений: ");
	int n=0, k=0;
	scanf("%d %d", &n, &k);
	if ((n<0)||(k<0)||(n>=k))
	{
		printf("\tДиапазон не оч\n");	
		return 1;
	}
	int Mas[k-n+1];
	eratosfen(Mas,k-n+1,n);
	prime_linear(Mas,k-n+1);
	output(Mas,k-n+1);
	return 0;
}


