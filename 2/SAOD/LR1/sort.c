#include <stdlib.h>
#include <stdint.h>

//==================================================
//					Insertion Sort
void InsertionSort(uint32_t a[], uint32_t size)
{
	uint32_t i, temp = 0;
	long int j;
	for(i=1; i < size; i++)
	{
		temp = a[i];
		j = i;
		while ((j-- > 0) && (temp < a[j - 1]))
			a[j + 1] = a[j];
		a[j] = temp;
	}
}

//==================================================
//					Bubble Sort

void Bubble_Sort(uint32_t a[], uint32_t size)
{
	uint32_t i, j, k, temp;
	for(i = 1; i < size; i ++)
		for(j = 0; j < size - 1; j++)
			if(a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
}

//==================================================
//					Counting Sort
void CountingSort(uint32_t array[], uint32_t size)
{
	uint32_t i = 0, max = 0, min = (uint32_t) - 1;
	// Максимальное значение uint32_t = 0xffffffff или 4294967295-1
	// Поиск максимального значения
	for(i = 0; i < size; i++)
		if(array[i] > max)
			max = array[i];
	// Поиск минимального значения
	for(i = 0; i < size; i++)
		if(array[i] < min)
			min = array[i];

	uint32_t j, z;
	uint32_t range = max - min + 1;
	uint32_t *count = malloc(range * sizeof(*array));

	// Обнуление массива
	for(i = 0; i < range; i++)
		count[i] = 0;
	// Подсчет числа уникальных значений
	for(i = 0; i < size; i++)
		count [array[i] - min]++;
	// Восстановление исходного массива по количеству уникальных значений
	for(i = min, z = 0; i <= max; i++)
		for(j = 0; j < count[i - min]; j++) 
			array[z++] = i;
	// Освобождение памяти
	free(count);
}

//==================================================
//					MergeSort
void merge(uint32_t arr[], uint32_t l, uint32_t m, uint32_t r)
{
	uint32_t i, j, k;			// Счетчики
	uint32_t n1 = m - l + 1;
	uint32_t n2 =  r - m;
	uint32_t L[n1], R[n2];		// Временные массивы

	// Присвоение во временные массивы левой части
	for(i = 0; i < n1; i++)
		L[i] = arr[l + i];
	// Присвоение во временные массивы правой части
	for(j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];

	// Слияние временных массивов в основной
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Занесение остатка левого временного массива в основной
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	// Занесение остатка правого временного массива в основной
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void MergeSort(uint32_t arr[], uint32_t Left, uint32_t Right)
{
	// Проверка границ. Левая должна быть меньше правой
	// Если это условие не выполняется, то обрабатывается фрагмент массива из 1го элемента
	if (Left < Right)
	{
		uint32_t m = Left + (Right - Left) / 2; //Same as (l+r)/2, but avoids overflow for large l and h
		MergeSort(arr, Left, m);
		MergeSort(arr, m + 1, Right);
		// Последнее cлияние
		merge(arr, Left, m, Right);
	}
}

//==================================================
//					QuickSort
/*
uint32_t Partition(uint32_t array[], uint32_t c, uint32_t b)
{
	uint32_t pivot, lower, upper, temp;
	pivot = array[c];
	lower = c + 1;
	upper = b;
	do
	{
		while (array[lower] <= pivot && lower <= upper)
			lower = lower + 1;
		while (array[upper] > pivot && lower <= upper)
			upper = upper - 1;
		if (lower <= upper)
		{
			temp = array[lower];
			array[lower] = array[upper];
			array[upper] = temp;
			lower = lower + 1;
			upper = upper - 1;
		}
	}
	while (lower <= upper);
	temp = array[upper];
	array[upper] = array[c];
	array[c] = temp;
	return upper;
}

void QuickSort(uint32_t array[], uint32_t c, uint32_t b)
{
	uint32_t k;
	if (c < b)
	{
		k = Partition(array, c, b);
		QuickSort(array, c, k-1);
		QuickSort(array, k+1, b);
	}
}
*/

void QuickSort(uint32_t array[], long int left, long int right) // Quick Sort
{
    int pivot, tmp;
    long int i = left, j = right;
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


//==================================================
//					Heap Sort
void BuildHeap(uint32_t *array, uint32_t size, uint32_t RootIndex)
{
	uint32_t ramification, value;
	value = array[RootIndex];

	while(RootIndex <= size/2)
	{
		ramification = 2 * RootIndex;
		if(ramification < size && array[ramification] < array[ramification + 1])
			ramification++;
		if(value >= array[ramification])
			break;
		array[RootIndex] = array[ramification];
		RootIndex = ramification;
	}
	array[RootIndex] = value;
}

void HeapSort(uint32_t *array, uint32_t size)
{
	int i;
	uint32_t buff;
	for(i = size / 2; i >= 0; i--)
		BuildHeap(array, size, i);
	while(size > 0)
	{
		buff = array[0];
		array[0] = array[size];
		array[size] = buff;
		BuildHeap(array, --size, 0);
	}
}



//==================================================
//					Radix Sort
void RadixSort(uint32_t array[], uint32_t size)
{
	int i, exp=1;
	uint32_t m=0;
	// Создание временного массива
	uint32_t *b = malloc(sizeof(uint32_t)*size);
	for(i=0; i < size; i++)
		if(array[i] > m)
			m = array[i];
	while(m / exp > 0)
	{
		int buff[10] = {0};
		for(i = 0; i < size; i++)
			buff[array[i] / exp % 10]++;
		for(i = 1; i < 10; i++)
			buff[i] += buff[i - 1];
		for(i = size - 1; i >= 0; i--)
			b[--buff[array[i] / exp % 10]] = array[i];
		for(i=0; i < size; i++)
			array[i] = b[i];
		exp *= 10;
	}
	free(b);
}

//==================================================
//					Odd-Even Sort
void Odd_even_iter(uint32_t a[], uint32_t n, uint32_t phase)
{
	uint32_t i, left, right, tmp;

	if (phase % 2 == 0)
		for (i = 1; i < n; i += 2)
		{
			left = i - 1;
			if (a[left] > a[i])
			{
				tmp = a[left];
				a[left] = a[i];
				a[i] = tmp;
			}
		}
	else
		for (i = 1; i < n-1; i += 2)
		{
			right = i+1;
			if (a[i] > a[right])
			{
				tmp = a[right];
				a[right] = a[i];
				a[i] = tmp;
			}
		}
}


void Odd_evenSort(uint32_t a[], uint32_t n)
{
	uint32_t i;
	for (i = 0; i < n; i++)
		Odd_even_iter(a, n, i);
}
