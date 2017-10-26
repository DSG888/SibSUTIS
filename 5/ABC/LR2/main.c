#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <fcntl.h>
#include <string.h>
#define SIZE 2000
//#define THR_NUM 4


int *alloc_matrix(int size)
{
	int *matrix = (int*)malloc(size * size * sizeof(int));
	printf("Матрица %d*%d создана\n", size, size);
	return matrix;
}
 
 
void del_matrix(int *matrix)
{
	free(matrix);
}
 
double dtime()
{
  struct timeval tv;
  struct timezone tz;
  double t;
  gettimeofday(&tv, &tz);
  t = (double)tv.tv_sec + (double)tv.tv_usec*1e-6;
  return(t);
}

struct matrix_args{
	int *m1;
	int *m2;
	int *ans;
	int size;
	int start;
	int end;
} ARG[THR_NUM];

void *multiply_matrix(void *pargs)
{
	struct matrix_args *args = (struct matrix_args *) pargs;
	int i, j, k, l, m, tmp = 0;
	double t0 = dtime();
	int *m1 = args->m1;
	int *m2 = args->m2;
	int *ans = args->ans;
	int size = args->size;
	int start = args->start;
	int end = args->end;
	for(i = start; i < end; i++)
	{									// строки первой матрицы
		m = i * size;
		for(j = 0; j < size; j++)
		{								// столбцы второй матрицы
			l = 0;
			for(k = 0; k < size; k++)
			{							// столбец первой/строка второй
				tmp += m1[m + k] * m2[j + l];
				l += size;
			}//k
			ans[m + j] = tmp;
			tmp = 0;
		}//j
	}//i
	printf("Время выполнения %fs\n", dtime() - t0);
	pthread_exit(NULL);
}
 
int main(int argc, char** argv)
{
	int i, j, size, k, step, pos, res;
	pthread_t threads[THR_NUM];
	pthread_attr_t attr;
	if(argc > 1)
		size = atoi(argv[1]);
	else
		size = SIZE;
	printf("Выделение памяти\n");
	int *m1 = alloc_matrix(size);
	int *m2 = alloc_matrix(size);
	int *ans = alloc_matrix(size);
	for(i=0; i<size; i++)
		for(j=0; j<size; j++)
		{
			m1[i + j * size] = 1;				//i* size +j;
			m2[i + j * size] = 1;				//i* 1000 +j;
		}
	printf("Умножение\n");
	double t0 = dtime();
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	step = (int)((double)size/(double)THR_NUM);
	pos = 0;
	for(k = 0; k < THR_NUM; k++)
	{
		ARG[k].m1 = m1;
		ARG[k].m2 = m2;
		ARG[k].ans = ans;
		ARG[k].size = size;
		ARG[k].start = pos;
		pos += step;
		ARG[k].end = (k == THR_NUM - 1) ? size : pos;
		res = pthread_create(&threads[k], &attr, multiply_matrix, (void *)&ARG[k]);
		if (res)
		{
			fprintf(stderr, "Поток не создан!\n");
			exit(1);
		}
	}
	pthread_attr_destroy(&attr);
	for(k = 0; k < THR_NUM; k++)
		pthread_join(threads[k], NULL);
	printf("Время выполнениея программы: %f\n", dtime() - t0);
	FILE *f = fopen("out", "w");
	printf("Вычисление\n");
	for (i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
			fprintf(f, "%d\t", ans[i*size + j]);
		fprintf(f, "\n");
	}
	fclose(f);
	del_matrix(m1);
	del_matrix(m2);
	del_matrix(ans);
	pthread_exit(NULL);
}
