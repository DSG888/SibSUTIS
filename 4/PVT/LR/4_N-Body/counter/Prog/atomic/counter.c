/*
 * counter.c: 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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
	
	double t = wtime();
	int count = 0;
	
	#pragma omp parallel for
	for (int i = 0; i < n; ++i)
	{
		if (v[i] == 3)
			#pragma omp atomic
			count++;
	//	(v[i] == 3) && (count++);
	}
	t = wtime() - t;
	printf("Counter (serial, n = %d)\n", n);	
	printf("Count = %d\n", count);	
	printf("Time (sec): %.6f\n", t);
	
	free(v);
	return 0;
}
