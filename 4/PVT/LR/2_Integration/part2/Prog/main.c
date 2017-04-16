#define _POSIX_C_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <omp.h>

//Ответ: 1.44418289875682

const double PI = 3.14159265358979323846;

const uint64_t n = 1000000000;	//


double getrand(unsigned int *seed)
{
	return (double)rand_r(seed) / RAND_MAX;
}

double func(double x, double y)
{
	return 3 * pow(y, 2) * pow(sin(x), 2);
}

double lin()
{
	unsigned int seed = omp_get_thread_num(); 
	uint64_t in = 0;
	double s = 0;
	double t = omp_get_wtime();
	
	for (uint64_t i = 0; i < n; ++i)
	{
		double x = getrand(&seed) * PI;
		double y = getrand(&seed);
		if (y <= sin(x))
		{
			++in;
			s += func(x, y);
		}
	}
	double v = PI * in / n;
	double res = v * s / in;
	
	t = omp_get_wtime() - t;
	printf("Result: %.12f, n %d\n", res, n);
	printf("Elapsed time (sec.): %.12f\n", t);
	return t;
}

double par()
{
	uint64_t in = 0;
	double s = 0;
	double t = omp_get_wtime();
	#pragma omp parallel
	{
		double s_loc = 0;
		uint64_t in_loc = 0;
		unsigned int seed = omp_get_thread_num(); 
		#pragma omp for nowait
		for (uint64_t i = 0; i < n; ++i)
		{
			double x = getrand(&seed) * PI;
			double y = getrand(&seed);
			if (y <= sin(x))
			{
				++in_loc;
				s_loc += func(x, y);
			}
		}
		#pragma omp atomic
		s += s_loc;
		#pragma omp atomic
		in += in_loc;
	}
	double v = PI * in / n;
	double res = v * s / in;
	t = omp_get_wtime() - t;
	printf("Result: %.12f, n %d\n", res, n);
	printf("Elapsed time (sec.): %.12f\n", t);
	return t;
}

int main()
{
	lin();
	par();
	return 0;
}
