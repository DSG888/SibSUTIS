#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PROJ_ID 1001

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};

int main(int argc, char *argv[])
{
    key_t key;
    int semid;
    struct sembuf lock_res = {0, -1, 0};
    struct sembuf rel_res = {0, 1, 0};
    struct sembuf push[2] = {{1, -1, IPC_NOWAIT}, {2, 1, IPC_NOWAIT}};
    struct sembuf slave_dec = {3, -1, 0};

    int i;

    key = ftok("/etc/fstab", PROJ_ID);

    /* Создать набор из трёх семафоров */
    if ((semid = semget(key, 4, 0666)) < 0) {
        perror("semget:");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 20; i++) {
        sleep(rand()%6);
        /* Попытаться заблокировать ресурс (семафор номер 0) */
        if (semop(semid, &lock_res, 1) == -1) {
            perror("semop:lock_res");
        }
        /* Уменьшить свободное место (семафор номер 1) /
           Добавить элемент (семафор номер 2) */
        if (semop(semid, &push[0], 2) != -1) {
            printf("---> Process:%d\n", getpid());
        }
        else {
            printf("---> Process:%d  BUFFER FULL\n", getpid());
        }
        /* Разблокировать ресурс */
        semop(semid, &rel_res, 1);
    }

    if (semop(semid, &slave_dec, 1) == -1) {
        perror("semop:slave_dec");
    }

    return 0;
}
