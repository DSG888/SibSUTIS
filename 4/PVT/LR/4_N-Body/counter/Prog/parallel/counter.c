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
	

	
	int count = 0;
	double t = wtime();
	
	
	#pragma omp parallel
	{
		int nthreads = omp_get_num_threads();
		int items_per_thread = n / nthreads;
		int threadid = omp_get_thread_num();
		int lb = threadid * items_per_thread;
		int ub = (threadid == nthreads - 1) ? (n) : (lb + items_per_thread);
		int c = 0;
		for (int i = lb; i < ub; ++i)
		{
			if (v[i] == 3)
				c++;
		}
		#pragma omp atomic
		count += c;
	}
	t = wtime() - t;
	printf("Counter (serial, n = %d)\n", n);	
	printf("Count = %d\n", count);	
	printf("Time (sec): %.6f\n", t);
	
	free(v);
	return 0;
}
