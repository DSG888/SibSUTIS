#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define __USE_XOPEN2K 1

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

pthread_spinlock_t spinlock;
void *counter_thread(void *counter)
{
	for (int i = 0; i < 5000000; i++)
	{
		pthread_spin_lock(&spinlock);
		++(*((int *)counter));
		pthread_spin_unlock(&spinlock);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	double t = wtime();
	pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
	int counter = 0;
	int nthreads = argc > 1 ? atoi(argv[1]) : 16;
	pthread_t *tids = malloc(sizeof(*tids) * nthreads);
	for (int i = 0; i < nthreads; i++)
	{
		if (pthread_create(&tids[i], NULL, counter_thread, (void *)&counter) != 0)
		{
			fprintf(stderr, "Can't create thread\n");
			exit(EXIT_FAILURE);
		}
	}
	for (int i = 0; i < nthreads; i++)
	pthread_join(tids[i], NULL);
	t = wtime() - t;
	printf("Counter (threads %d, counter %d): %.6f sec.\n", nthreads, counter, t);
	pthread_spin_destroy(&spinlock);
	free(tids);
	return 0;
}
