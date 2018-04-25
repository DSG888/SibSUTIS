#include <unistd.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);


	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	char buf[100000];
	double t = MPI_Wtime();
	if (rank == 0)
	{
		MPI_Send(&buf[0], 100000, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&buf[0], 100000, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	else
	if (rank == 1)
	{
		
		MPI_Recv(&buf[0], 100000, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);		
		MPI_Send(&buf[0], 100000, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}
	t = MPI_Wtime()-t;
	printf("SP %.6f\n", 2*100000/t);

	MPI_Finalize();
	return 0;
}
