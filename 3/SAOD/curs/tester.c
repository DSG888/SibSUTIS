#include "tester.h"

int getrand(int min, int max)
{
	return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void QuickSort(int array[], int left, int right)
{
	int pivot, tmp;
	int i = left, j = right;
	pivot = array[(i + j) / 2];		// Получение опорного элемента
	do
	{
		while (array[i] < pivot)
			i++;
		while (array[j] > pivot)
			j--;
		if (i <= j )
		{
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
			i++;
			j--;
		}
	}
	while (i < j);

	if (left < j)
		QuickSort(array, left, j);
	if (i < right)
		QuickSort(array, i, right);
}

int *getrandmas(int size)
{
	int *tmpmas = malloc(sizeof(int) * size);
	int *mas = malloc(sizeof(int) * size);
	//TODO Проверка
	int i, r, s = 0;;
	for (i = size; 0 < i; --i)
	{
		tmpmas[i - 1] = i;
	}
	for (i = 0; size > i; ++i)
	{
		while(1)
		{
			if ((i) && ( (i-s) >= (size-i) ))
		//	if ((i) && ( (i-s) >= size/2.1 ))//i->0
			{
				QuickSort(tmpmas, s, size - 1);
				s = i;
			}
			r = getrand(s, size);
			if (tmpmas[r])
			{
				mas[i] = tmpmas[r];
				tmpmas[r] = 0;
				break;
			}
		}
	}
	free(tmpmas);
	return mas;
}
