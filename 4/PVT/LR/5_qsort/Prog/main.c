#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define swap(d,a,b) {uint32_t dt = d[b]; d[b] = d[a]; d[a] = dt;}

void QSortPar(uint32_t *data, uint32_t start, uint32_t end)
{
	uint32_t splitmas (uint32_t *a, uint32_t upper)
	{
		uint32_t  p = 0, q = upper - 1;
		while (q >= p)
		{
			while (q>=p && a[p] <= a[0])
				p++;
			while (q>=p && a[q] > a[0])
				q--;
			if (q > p)
				swap(a,p,q);
		}
		swap(a, 0, q);
		return q ;
	}

	if (start + 1 >= end)
		return;
	
	if (start + 2 == end)
	{
		if (data[start] > data[start + 1])
		{
			swap(data, start, start + 1);
		}
	}
	else
		if (start + 1 < end)
		{
			uint32_t size = end - start;
			uint32_t store = start + splitmas(data + start, size);
			#pragma omp task if (size > 200)
			{
				QSortPar(data, start, store);
			}
			#pragma omp task if (size > 200)
			{
				QSortPar(data, store + 1, end);
			}
		}
	return;
}

void quicksort(uint32_t *data, uint32_t size)
{
	#pragma omp parallel
	{
		#pragma omp single nowait
		{
			QSortPar(data, 0, size);
		}
	}
}












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
	int Gen = 0;
	// Проверка аргументов. Если не получено 3 аргумента, опросить пользователя
	if (argc != 3)
	{
		printf(":(\n");
		return 1;
	}
	else
	{
		// Из параметров запуска
		LEN = atol(argv[1]);
		Gen = atoi(argv[2]);
	}

	// Проверка входных данных
	if ( (0 > Gen)||(4 < Gen)||(2 > LEN))
	{
		printf("\n\tСломано!\n");
		return 1;
	}
	// Выделение памяти в динамической памяти
	uint32_t *Mas = (uint32_t *)malloc(LEN * sizeof(int32_t));
	uint32_t *Mas2 = (uint32_t *)malloc(LEN * sizeof(int32_t));

	// Если память не выделилась
	if (Mas == NULL)
		return 2;
	if (Mas2 == NULL)
		return 2;

	double t;			// Для времени запуска алгоритма

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

	quicksort(Mas,LEN);
	
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
