#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

const double a = -4.0;
const double b = 4.0;
const unsigned int n = 1000000000;
pthread_mutex_t mutex_sum = PTHREAD_MUTEX_INITIALIZER;
// Глобальная сумма
double s = 0.0;
double func(double x)
{
	return exp(-x * x);
}

struct thread_data {
	pthread_t tid;
	int threadno;
	int nthreads;
};

void *integrate(void *arg)
{
	struct thread_data *p = (struct thread_data *)arg;
	double h = (b - a) / n;
	int points_per_proc = n / p->nthreads;
	int lb = p->threadno * points_per_proc;
	int ub = (p->threadno == p->nthreads - 1) ? (n - 1) : (lb + points_per_proc - 1);
	double locs = 0.0;
	for (int i = lb; i < ub; i++)
	locs += func(a + h * (i + 0.5));
	locs *= h;
	pthread_mutex_lock(&mutex_sum);
	s += locs;
	pthread_mutex_unlock(&mutex_sum);
	return NULL;
}

// Порядковый номер потока 0, 1, 2, ...
// Количество потоков
int main(int argc, char **argv)
{
	int nthreads = (argc > 1) ? atoi(argv[1]) : 2;
	printf("Numerical integration (%d threads): [%f, %f], n = %d\n", nthreads, a, b, n);
	struct thread_data *tdata = malloc(sizeof(*tdata) * nthreads);
	if (tdata == NULL)
	{
		fprintf(stderr, "No enough memory\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i < nthreads; i++)
	{
		// Запуск nthreads - 1 потоков!
		tdata[i].threadno = i;
		tdata[i].nthreads = nthreads;
		if (pthread_create(&tdata[i].tid, NULL, integrate, &tdata[i]) != 0)
		{
			fprintf(stderr, "Can't Numerical create thread\n");
			exit(EXIT_FAILURE);
		}
	}
	tdata[0].threadno = 0;
	tdata[0].nthreads = nthreads;
	integrate(&tdata[0]);
	for (int i = 1; i < nthreads; i++)
		pthread_join(tdata[i].tid, NULL);
	free(tdata);
	printf("Result Pi: %.12f\n", s * s);
	return 0;
}

