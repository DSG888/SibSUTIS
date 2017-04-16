//Параллельный алгоритм интегрирования методом средних прямоугольников: циклическое распределение

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <inttypes.h>
#include <omp.h>
#include <math.h>

inline double func(double x);

double func(double x)
{
	return exp(-x * x);
}

int main(int argc, char **argv)
{
	printf("Version: 2\n");
	for (uint64_t i = 0; i < 1000000000; ++i)
	{
		uint64_t j;
		j = i * i / (1 + i * i);
	}
	
	const double a = -8.0;
	const double b = 8.0;
	const uint64_t n = 30000000000;
	printf("Numerical integration: [%f, %f], n = %" PRIu64 "\n", a, b, n);
	double h = (b - a) / n;
	
	double s = 0.0;
	double t = omp_get_wtime();
	#pragma omp parallel
	{
		double sloc = 0.0;
		int nthreads = omp_get_num_threads();
		int tid = omp_get_thread_num();
		uint64_t points_per_thread = n / nthreads;
		uint64_t lo = tid * points_per_thread;
		uint64_t hi = (tid == nthreads - 1) ? n - 1 : lo + points_per_thread;

	//	#pragma omp for nowait
		for (uint64_t i = lo; i <= hi; ++i)
			sloc += func(a + h * (i + 0.5));
		#pragma omp atomic
		s += sloc;
	}
	s *= h;
	t = omp_get_wtime() - t;
	printf("Result Pi: %.20f\n", s * s);
	printf("Elapsed time (sec.): %.12f\n", t);
	return 0;
}
