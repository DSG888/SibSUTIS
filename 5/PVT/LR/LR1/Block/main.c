#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>



int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int commsize, rank, *rbuf, *sbuf;
    double t;
    MPI_Request *r;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);

    int bblock = 4, ss, dest;
    rbuf = malloc(sizeof(int) * commsize);
    sbuf = malloc(sizeof(int) * commsize);
    r = malloc(2 * bblock * sizeof(MPI_Request));

    t = MPI_Wtime();

    for (int i = 0; i < commsize; ++i)
    {
        sbuf[i] = rank;
        rbuf[i] = -1;
    }
    //sbuf[rank] = rank;
    //rbuf[rank] = rank;

    t = MPI_Wtime();
    for (int ii = 0; ii < commsize; ii += bblock)
    {
        ss = commsize - ii < bblock ? commsize - ii : bblock;

        for (int i = 0 ; i < ss; ++i)
        {
            dest = (rank + i + ii) % commsize;
            MPI_Irecv(&rbuf[dest], 1, MPI_INT, dest, 0, MPI_COMM_WORLD, &r[i]);
        }

        for (int i = 0; i < ss; ++i)
        {
            dest = (rank - i - ii + commsize) % commsize;
            MPI_Isend(&sbuf[dest], 1, MPI_INT, dest, 0, MPI_COMM_WORLD, &r[i + ss]);
        }
        MPI_Waitall(ss * 2, r, MPI_STATUSES_IGNORE);
    }
    t = MPI_Wtime() - t;

    printf("Процесс %d\tsbuf:", rank);
    for (int i = 0; i < commsize; ++i)
        printf("\t[%d]: %d", i, sbuf[i]);
    printf("\n");

    printf("Процесс %d\trbuf:", rank);
    for (int i = 0; i < commsize; ++i)
        printf("\t[%d]: %d", i, rbuf[i]);
    printf("\n\n");

    printf("Процесс %d  time: %f\n", rank, t);

    free(sbuf);
    free(rbuf);
    free(r);
    MPI_Finalize();
    return 0;
}
