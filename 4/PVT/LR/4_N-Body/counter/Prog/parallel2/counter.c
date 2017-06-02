/*
 * counter.c: 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main(int argc, char *argv[])
{
	int n = 100000000;
	int *v = malloc(sizeof(*v) * n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < n/1000; ++j)
			v[j] = j;
		v[i] = rand() % 30;
	}
	
	int nthreads = 0;
	#pragma omp parallel
	{
		nthreads = omp_get_num_threads();
	}
	
	int *c = malloc(sizeof(*c) * nthreads);
	for (int i = 0; i < nthreads; ++i)
	{
		c[i] = 0;
	}
	
	
	int count = 0;
	double t = wtime();
	
	
	#pragma omp parallel for
	for (int i = 0; i < n; ++i)
	{
		if (v[i] == 3)
			c[omp_get_thread_num()]++;
	}
	
	
	t = wtime() - t;
	
	for (int i = 0; i < nthreads; ++i)
		count += c[i];
	
	printf("Counter (serial, n = %d)\n", n);	
	printf("Count = %d\n", count);	
	printf("Time (sec): %.6f\n", t);
	free(c);
	free(v);
	return 0;
}
