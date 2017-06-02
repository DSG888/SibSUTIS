/* Решение систем линейных уравнений методом Гаусса */
#include <stdio.h>
#include <stdlib.h>
#define N 3

float matr[N][N + 1];
void show();			/* Выводит на экран матрицу */
int gauss(float []);	/* Обрабатывает матрицу */

void main()
{
	int i, j;
	float *out = new float;
	randomize();
	for (i = 0; i < N; ++i)
		for (j = 0; j <= N; ++j)
			matr[i][j] = rand() % 100;
	printf(" --- Исходная матрица --- \n\n");
	show();
	gauss(out);
	printf("\n ---- Вектор ответов ---- \n\n");
	for(i = 0; i < N; ++i)                              
		printf(" x%d = %5.3f", i + 1, out[i]);   
}

/* Выводит на экран матрицу */
void show()
{
	int i, j;
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j <= N; ++j)
			printf("%8.3f  ", matr[i][j]);
		printf("\n");
	}
}

/* Обрабатывает матрицу */
int gauss(float out[])
{
	int i, j, k, l;
	float tmp, buf[N];
	/* Прямой ход */
	for(i = 0; i < N; ++i)  
		for(j = i + 1; j < N; ++j)
		{
			for(l = 0; l < N; ++l)
				if (matr[i][i] < matr[l][i])
				{
					for (k = 0; k < N; ++k)
					{
						buf[k] = matr[i][i];
						matr[i][i] = matr[l][i];
						matr[l][i] = buf[k];
					}
				}
			tmp =- matr[i][i] / matr[j][i]; /* Нахождение ведущего элемента */
			for (k = i; k <= N; ++k)
				matr[j][k] = matr[j][k] * tmp + matr[i][k]; /* Зануление столбца */
		}
        printf("\n");
        show();
        /* Обратный ход */
	for(i = N, k = N - 1; k >= 0; --k)
	{
		i--;
		out[k] = matr[k][N] / matr[k][i];
		for (j = 0; j < k + 1; ++j)
			matr[k - j][N] -= matr[k - j][i] * out[k];
	}
}
