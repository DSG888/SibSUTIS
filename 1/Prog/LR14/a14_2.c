/*
Дана последовательность действительных чисел а 1 , а 2 , ..., а n и число x. Выяснить, является ли a возрастающей или убывающей. Если является, то вставить в нее элемент x так, чтобы порядок не был нарушен. Например:
	Вход: а = 3 10 15 32 12; х = 12.
	Выход: 3 10 12 15 32 12

	Вход: а = 40 37 32 15 14 7; х = 20.
	Выход: 40 37 32 20 15 14 7

	Вход: а = 40 37 50 15 14 7; х = 20.
	Выход: 40 37 50 15 14 7 (не изменена).
*/

#include <stdio.h>
#include <time.h>

void GenRandMas(int* arr, const int len, const int l, const int r)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < len; i++)
		arr[i]= (l - 1 + rand() % r + 2);
}

void SortMP(int* arr, const int len)
{
	int i = 0, j = 0, tmp = 0;
	for(i = 0 ; i < len - 1; i++)
	{
		for(j = 0 ; j < len - i - 1 ; j++)
		{
			if(arr[j] > arr[j+1])
			{
				tmp = arr[j];
				arr[j] = arr[j+1] ;
				arr[j+1] = tmp;
			}
		}
	}
}

void InvMas(int MasX[], int M)
{
	int i, tmpMas[M];
	for (i = M - 1; i >= 0; i--)
	{
		tmpMas[M - i - 1] = MasX[i];
	}
	for (i = 0; i < M; i++)
	{
		MasX[i] = tmpMas[i];
	}
}

void output(int MasX[], int M)
{
	int i;
	printf("\t[");
	for (i = 0; i < M; i++)
	{
		i < M - 1 ? printf("%d,", MasX[i]) : printf("%d]\n", MasX[i]);
	}
}

int main ()
{
	srand(time(NULL));
	int a = 0;
	printf("Введите число элементов массива (1-100): ");
	scanf("%d", &a);
	if ((a > 100) || (a < 1))
	{
		printf("\tЧисло нужно от 1-100\n");
		return 1;
	}
	int Mas[a];
	GenRandMas(Mas, a, 0, 100);		// Получение случайного массива
	printf("\tСлучайный массив:");
	output(Mas, a);					//	Вывод случайного массива

	if (rand() % 2)
	{
		printf("\t\x1b[1;31mХочу отсортированный массив!\x1b[0m\n");
		SortMP(Mas, a);						//	Сортировка
		printf("\tОтсортированный массив:");
		output(Mas, a);						//	Вывод отсортированного массива
		if (rand() % 2)
		{
			printf("\t\x1b[1;31mХочу обратный отсортированный массив!\x1b[0m\n");
			InvMas(Mas, a);					//	Инверсия массива
			printf("\tИнвертированный массив:");
			output(Mas, a);					//	Вывод инвертированного массива

		}
	}
	printf("\t\x1b[1;31m=========================================\x1b[0m\n");
	int x=0;
	printf("Какое число вставить в массив? x = ");
	scanf("%d", &x);
	int R = 0, L = 0, i, j = 0;
	for (i = 1; i < a; i++)						//	Получение характеристики массива
	{
//		R=R+(!(Mas[i]>=Mas[i-1]));			//	I
//		L=L+(!(Mas[i]<=Mas[i-1]));

//		if (!(Mas[i]>=Mas[i-1]))			//	II
//			R++;
//		else
//			if (!(Mas[i]<=Mas[i-1]))
//				L++;

		L = L + (Mas[i] > Mas[i - 1]);				//	III
		R = R + (Mas[i] < Mas[i - 1]);
	}
	if ( (R) && (L) )
	{
		printf("\tМассив не изменился. Последовательность не возрастает и не убывает\n");
		output(Mas, a);
		return 0;
	}
	int NewMas[a + 1];
	if (!(R))
	{
		for (i = 0; i < a; i++)				//	Занесение всего до X
			if (Mas[i] <= x)
			{
				NewMas[j] = Mas[i];
				j++;
			}
			else
			{
				NewMas[j] = x;
				j++;
				break;
			}
		for (i = j; i < a + 1; i++)			//	Занесение всего после X
			NewMas[i] = Mas[i - 1];
	}

	if (!(L))
	{
		for (i = 0; i < a; i++)				//	Занесение всего до X
			if (Mas[i] >= x)
			{
				NewMas[j] = Mas[i];
				j++;
			}
			else
			{
				NewMas[j] = x;
				j++;
				break;
			}
		if (i == a)						//	Интегрированный костыль
			NewMas[a] = x;				//	Шоб вставить в конец X. Если он минимальный.
		else
			for (i = j; i < a + 1; i++)		//	Занесение всего после X
				NewMas[i] = Mas[i - 1];
	}
	output(NewMas, a + 1);
	return 0;
}
