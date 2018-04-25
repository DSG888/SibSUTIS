#include <unistd.h>
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);


	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int *mainbuf = malloc(sizeof(int)*size);
	int i;
	for (i = 0; i < size; ++i)
		mainbuf[i] = -1;
	mainbuf[rank] = rank;
	
	
	
	
//	for (i = 0; i < size -1;++i)
//	{
//		int p = (i + size + 1 + rank) % size;	// Назначение
//		printf("Я процесс %d и я буду передавать процессу %d\n", rank, p);
//		MPI_Sendrecv(&mainbuf[rank], 1, MPI_INT, p, 0, &mainbuf[p], 1, MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//	
//	}


	int r = (rank-1+size)%size;
	int s = rank;

	double t = MPI_Wtime();
	for (i = 0; i<size-1; ++i)
	{
		printf("Я процесс %d и я буду передавать процессу %d и принимать от процесса %d\n", rank, (rank+1)%size, (rank-1+size)%size);
		MPI_Sendrecv(&mainbuf[s], 1, MPI_INT, (rank+1)%size, 0, &mainbuf[r], 1, MPI_INT, (rank-1+size)%size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		s = r;
		r = (r-1+size)%size;
	}
	t = MPI_Wtime() - t;

	for (i=0; i < size; ++i)
	{
		//sleep(rank+1);
		if (!(i))
			printf("Я процесс %d. Мой буфер: [%d, ", rank, mainbuf[i]);
		else
			if (i == size - 1)
				printf("%d]\n", mainbuf[i]);
			else
				printf("%d, ", mainbuf[i]);
	//printf("%f\n", t);
	}
	printf("%f\n", t);
	free(mainbuf);
//	char buf[100000];
//	double t = MPI_Wtime();
//	if (rank == 0)
//	{
//		MPI_Send(&buf[0], 100000, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
//		MPI_Recv(&buf[0], 100000, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//	}
//	else
//	if (rank == 1)
//	{
//		
//		MPI_Recv(&buf[0], 100000, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);		
//		MPI_Send(&buf[0], 100000, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
//	}
//	t = MPI_Wtime()-t;
//	printf("SP %.6f\n", 2*100000/t);

	MPI_Finalize();
	return 0;
}
