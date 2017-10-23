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
    union semun arg;
    struct sembuf lock_res = {0, -1, 0};
    struct sembuf rel_res = {0, 1, 0};
    struct sembuf pop[2] = {{1, 1, IPC_NOWAIT}, {2, -1, IPC_NOWAIT}};
    struct sembuf wait_slave = {3, 0, IPC_NOWAIT};

    if(argc < 2){
        printf("Usage: bufdemo [dimensione]\n");
        exit(0);
    }

    key = ftok("/etc/fstab", PROJ_ID);

    /* Создать набор из четырех семафоров */
    if ((semid = semget(key, 4, 0666 | IPC_CREAT)) < 0) {
        perror("semget:");
        exit(EXIT_FAILURE);
    }

    /* Установить в семафоре номер 0 (Контроллер ресурсов)
       значение "1" */
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    /* Установить в семафоре номер 1 (Контроллер свободного места)
       значение длины буфера */
    arg.val = atol(argv[1]);
    semctl(semid, 1, SETVAL, arg);

    /* Установить в семафоре номер 3 (Количество slave процессов)
       значение колчиства slave процессов */
    arg.val = atol(argv[2]);
    semctl(semid, 3, SETVAL, arg);

    /* Установить в семафоре номер 2 (Контроллер элементов в буфере)
       значение "0" */
    arg.val = 0;
    semctl(semid, 2, SETVAL, arg);

    while (semop(semid, &wait_slave, 1) == -1) {
        sleep(rand()%3);
        /* Попытаться заблокировать ресурс (семафор номер 0)*/
        if (semop(semid, &lock_res, 1) == -1){
            perror("semop:lock_res");
        }
        /* Увеличить свободное место (семафор номер 1) /
           Взять элемент (семафор номер 2) */
        if (semop(semid, &pop[0], 2) != -1){
            printf("<--- Process:%d\n", getpid());
        }
        else printf("<--- Process:%d  BUFFER EMPTY\n", getpid());
        /* Разблокировать ресурс */
        semop(semid, &rel_res, 1);
    }

    /* Удалить семафоры */
    semctl(semid, 0, IPC_RMID);

    return 0;
}
