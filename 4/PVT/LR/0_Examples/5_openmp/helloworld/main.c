#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
	#pragma omp parallel
	/* <-- Fork */
	{
		printf("Hello, multithreaded world: thread %d of %d\n",
		omp_get_thread_num(), omp_get_num_threads());
	}
	return 0;
}
