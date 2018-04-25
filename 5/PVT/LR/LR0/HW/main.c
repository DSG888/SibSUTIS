#include <unistd.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	printf("Hello from %d of %d\n", rank, size);
	
	MPI_Finalize();
	return 0;
}
