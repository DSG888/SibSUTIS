/*
 * Решение СЛАУ методом Гаусса. Распределение данных - циклическими
 * горизонтальными полосами.
 * (Запуск задачи на 8-ми компьютерах).
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>

/* 
 * Каждая ветвь задает размеры своих полос матрицы MA и вектора правой части.
 * (Предполагаем, что размеры данных делятся без остатка на количество
 * компьютеров.) 
 */

#define M 400
#define N 50
#define tegD 1

/* Описываем массив для циклических полос исходной матрицы - MA и вектор V для
 * приема данных. Для простоты, вектор правой части уравнений присоединяем
 * дополнительным столбцом к матрице коэффициентов. В этом дополнительном
 * столбце и получим результат. */

double MA[N][M+1], V[M+1], MAD, R;

 

int main(int args, char **argv)
{ 
	int	size, MyP, i, j, v, k, k1, p;
	int	*index, *edges;
	MPI_Comm   comm_gr;
	struct timeval tv1, tv2;
	int dt1;
	int reord = 1;

	/* Инициализация библиотеки */
	MPI_Init(&args, &argv);
	/* Каждая ветвь узнает размер системы */
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	/* и свой номер (ранг) */
	MPI_Comm_rank(MPI_COMM_WORLD, &MyP);

 /* Выделяем память под массивы для описания вершин и ребер в топологии
  * полный граф */

	index = (int *)malloc(size * sizeof(int));
	edges = (int *)malloc(size*(size-1)*sizeof(int));

 /* Заполняем массивы для описания вершин и ребер для топологии
  * полный граф и задаем топологию "полный граф". */
	for(i = 0; i < size; i++)
	{
		index[i] = (size - 1)*(i + 1);
		v = 0;
		for(j = 0; j < size; j++)
		{
			if(i != j)
				edges[i * (size - 1) + v++] = j;
		}
	}
	MPI_Graph_create(MPI_COMM_WORLD, size, index, edges, reord, &comm_gr);
 /* Каждая ветвь генерирует свои циклические полосы матрицы A и свой отрезок
  * вектора правой части, который присоединяется дополнительным столбцом к A.
  * Нулевая ветвь генерирует следующие строки исходной матрицы: 0, size,
  * 2*size, 3*size, и т.д. Первая ветвь - строки: 1, 1+size, 1+2*size, 1+3*size
  * и т.д. Вторая ветвь - строки: 2, 2+size, 2+2*size, 2+3*size и т.д.
  * (По диагонали исходной матрицы - числа = 2, остальные числа = 1). */

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
		{
			if((MyP+size*i) == j)
				MA[i][j] = 2.0;
			else
				MA[i][j] = 1.0;
		}
		MA[i][M] = 1.0*(M)+1.0;
	}
 /* Каждая ветвь засекает начало вычислений и производит вычисления */
	gettimeofday(&tv1, (struct timezone*)0);
 /* Прямой ход */
 /* Цикл k - цикл по строкам. Все ветви, начиная с нулевой, последовательно
  * приводят к диагональному виду свои строки. Ветвь, приводящая свои строки
  * к диагональному виду, назовем активной, строка, с которой производятся
  * вычисления, так же назовем активной. */
	for(k = 0; k < N; k++)
	{
	/* Цикл p - цикл по компьютерам. (Все веиви "крутят" этот цикл). */
		for(p = 0; p < size; p++)
		{
			if(MyP == p)
			{
			 /* Активная ветвь с номером MyP == p приводит свою строку с
			  * номером k к диагональному виду.
			  * Активная строка - k передается всем ветвям. */
				MAD = 1.0/MA[k][size*k+p];
				for(j = M; j >= size*k+p; j--)
				MA[k][j] = MA[k][j] * MAD;
				for(j = 0; j <= M; j++)
				V[j] = MA[k][j];
				MPI_Bcast(V, M+1, MPI_DOUBLE, p, comm_gr);
				for(i = k+1; i < N; i++)
				{
					for(j = M; j >= size*k+p; j--)
					MA[i][j] = MA[i][j]-MA[i][size*k+p]*MA[k][j];
				}
			}

		 /* Работа принимающих ветвей с номерами MyP < p */
			else
				if(MyP < p)
				{
					MPI_Bcast(V, M+1, MPI_DOUBLE, p, comm_gr);
					for(i = k+1; i < N; i++)

					{
						for(j = M; j >= size*k+p; j--)
							MA[i][j] = MA[i][j] - MA[i][size*k+p]*V[j];
					}
				}
		  /* Работа принимающих ветвей с номерами MyP > p */
				else
					if(MyP > p)
					{MPI_Bcast(V, M+1, MPI_DOUBLE, p, comm_gr);
					   for(i = k; i < N; i++)
						 {
							 for(j = M; j >= size*k+p; j--)
								MA[i][j] = MA[i][j] - MA[i][ size*k+p]*V[j];
						 }
					}
		}			/*for p */
	}			/*for k */

/* Обратный ход */

 /* Циклы по k и p аноалогичны, как и при прямом ходе. */

	for(k1 = N-2, k = N-1; k >= 0; k--,k1--)
	{
		for(p = size-1; p >= 0; p--)
		{
			if(MyP == p)
			{
			  /* Работа активной ветви */
				R = MA[k][M];
				MPI_Bcast(&R, 1, MPI_DOUBLE, p, comm_gr);
				for(i = k-1; i >= 0; i--)
					MA[i][M] -= MA[k][M]*MA[i][size*k+p];
			}

		  /* Работа ветвей с номерами MyP < p */

			else
				if(MyP < p)
				{
					MPI_Bcast(&R, 1, MPI_DOUBLE, p, comm_gr);
					for(i = k; i >= 0; i--)
						MA[i][M] -= R*MA[i][ size*k+p];
				}

		  /* Работа ветвей с номерами MyP > p */

				else
					if(MyP > p)

					{
						MPI_Bcast(&R, 1, MPI_DOUBLE, p, comm_gr);
						for(i = k1; i >= 0; i--)
							MA[i][M] -= R*MA[i][size*k+p];
					}

		}			/* for p */

	}			/* for k */
 /* Все ветви засекают время и печатают */
	gettimeofday(&tv2, (struct timezone*)0);
	dt1 = (tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec;
	printf("MyP = %d Time = %d\n", MyP, dt1);
 /* Все ветви печатают, для контроля, свои первые четыре значения корня */
	printf("MyP = %d %f %f %f %f\n", MyP, MA[0][M],MA[1][M],MA[2][M],MA[3][M]);
 /* Все ветви завершают выполнение */
	MPI_Finalize();
	return(0);
}
