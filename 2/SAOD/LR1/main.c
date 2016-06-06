#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sort.h"

//Counting Sort
//Insertion Sort
//QuickSort
/*
	Параметры запуска:
	1: Число элементов массива
	2: Входной массив
		1 Случайный массив
		2 Отсортированный по убыванию
		3 Отсортированный по возрастанию
		4 Почти отсортированный по возрастанию	#FIXME
	3: Алгоритм
	!	1 Insertion Sort
		2 Bubble Sort
	!	3 Counting Sort
		4 Merge Sort
	!	5 Quick Sort
		6 Heap Sort
		7 Radix Sort
		8 Odd-Even Sort

*/

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
	return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main(int argc, char **argv)
{
	uint32_t LEN, i, HASH = 0;
	int Alg = 0, Gen = 0;
	// Проверка аргументов. Если не получено 4 аргумента, опросить пользователя
	if (argc != 4)
	{
		// Опрос пользователя
		// Пользователь выбирает размер массива
		printf("\tРазмер массива (число)? ");
		scanf("%lu", &LEN);
		// Пользователь выбирает алгоритм
		printf("\tВыбор алгоритма:\n\t  [1] Insertion Sort\n\t  [2] Bubble Sort\n\t  [3] Counting Sort\n\t  [4] Merge Sort\n\t  [5] Quick Sort\n\t  [6] Heap Sort\n\t  [7] Radix Sort\n\t  [8] Odd-Even Sort\n\tКакой алгоритм использовать? ");
		scanf("%d", &Alg);
		// Пользователь выбирает способ генерации массива
		printf("\tСортируемый массив\n\t  [1] Случайный массив (1-100млн)\n\t  [2] Отсортированный по убыванию\n\t  [3] Отсортированный по возрастанию\n\t  [4] Почти отсортированный по возрастанию\n\tКакой массив создать? ");
		scanf("%d", &Gen);
	}
	else
	{
		// Из параметров запуска
		LEN = atol(argv[1]);
		Gen = atoi(argv[2]);
		Alg = atoi(argv[3]);
	}

	// Проверка входных данных
	if ( (0 > Gen)||(4 < Gen)||(0 > Alg)||(8 < Alg)||(2 > LEN))
	{
		printf("\n\tСломано!\n");
		return 1;
	}
	printf("\n");
	// Выделение памяти в динамической памяти
	uint32_t *Mas = (uint32_t *)malloc(LEN * sizeof(int32_t));


	// Если память не выделилась
	if (Mas == NULL)
		return 2;

	double t;			// Для времени запуска алгоритма

	switch (Alg)
	{
		case 1:
			printf("\tАлгоритм сортировки: Insertion Sort\n");
			break;
		case 2:
			printf("\tАлгоритм сортировки: Bubble Sort\n");
			break;
		case 3:
			printf("\tАлгоритм сортировки: Counting Sort\n");
			break;
		case 4:
			printf("\tАлгоритм сортировки: Merge Sort\n");
			break;
		case 5:
			printf("\tАлгоритм сортировки: Quick Sort\n");
			break;
		case 6:
			printf("\tАлгоритм сортировки: Heap Sort\n");
			break;
		case 7:
			printf("\tАлгоритм сортировки: Radix Sort\n");
			break;
		case 8:
			printf("\tАлгоритм сортировки: Odd-Even Sort\n");
			break;
	}

	// Создание случайного массива
	if (Gen == 1)
	{
		for (i = 0; i < LEN; i++)
		{
			Mas[i] = getrand(1, 10000)*getrand(1, 10000);
			HASH += Mas[i];
		}
		printf("\tСоздан случайный массив из %d элементов\n", LEN);
	}
	else
		// Создание массива упорядоченного по убыванию
		if (Gen == 2)
		{
			for (i = 0; i < LEN; i++)
			{
				Mas[i] = LEN - i;
				HASH += Mas[i];
			}
			printf("\tСоздан массив отсортированный по убыванию из %d элементов\n", LEN);
		}
		else
			// Создание массива упорядоченного по возрастанию
			if (Gen == 3)
			{
				for (i = 0; i < LEN; i++)
				{
					Mas[i] = i;
					HASH += Mas[i];
				}
				printf("\tСоздан массив отсортированный по возрастанию из %d элементов\n", LEN);
			}
			else
				// Создание массива почти упорядоченного по возрастанию
				if (Gen == 4)
				{
					int tmp = rand() % (LEN-1);
					printf("%d\n", tmp);
					for (i = 0; i < LEN; i++)
					{
						Mas[i] = i;
						HASH += Mas[i];
					}
					printf("\tСоздан массив почти отсортированный по возрастанию из %d элементов\n", LEN);
				}

	t = wtime();				// Начало отсчета

	// Автор умеет case.
	if (Alg == 1)
		InsertionSort(Mas,LEN);
	if (Alg == 2)
		Bubble_Sort(Mas,LEN);
	if (Alg == 3)
		CountingSort(Mas,LEN);
	if (Alg == 4)
		MergeSort(Mas,0,LEN-1);
	if (Alg == 5)
		QuickSort(Mas,0,LEN-1);
	if (Alg == 6)
		HeapSort(Mas,LEN-1);
	if (Alg == 7)
		RadixSort(Mas,LEN);
	if (Alg == 8)
		Odd_evenSort(Mas,LEN);

	
	t = wtime() - t;			// Конец отсчета

	printf("\tВремя выполнения: %.6f секунд\n", t);

	// Проверка
	for (i = 0; i < LEN - 1; i++)
	{
		HASH -= Mas[i];
		//printf(" %d",Mas[i]);
		if (Mas[i] > Mas[i + 1])
		{
			printf("\tМассив НЕ отсортирован по неубыванию!\n");
			return 3;
		}
	}
	printf("\tМассив отсортирован по неубыванию\n");
	HASH -= Mas[LEN - 1];
	if (!(HASH))
		printf("\tМассив не искажен\n");
	else
		printf("\tМассив ИСКАЖЕН!\n");

	free(Mas);
	return 0;
}
