#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shmem_msg.h"

#define PROJ_ID 1001
#define SHARED_MEM_SIZE 4096

int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    message_t *msg = NULL;
    void *shmem_segment = NULL;

    key = ftok("/etc/fstab", PROJ_ID);

//    if ((shmid = shmget(key, SHARED_MEM_SIZE, 0666)) < 0) {
//       perror("shmget:");
//        exit(EXIT_FAILURE);
//    }

    if ((shmem_segment = shmat(shmid, NULL, 0)) == (void *)-1) {
        perror("shmat:");
        exit(EXIT_FAILURE);
    }

    while (1) {
        msg = shmem_recv_msg(shmem_segment);
        printf("type = %d\n", msg->type);
        printf("msg = %s\n", msg->payload);
        if (msg->type == MSG_FINALIZE)
            break;
    }

    if (shmdt(shmem_segment) == -1) {
        perror("shmdt:");
        exit(EXIT_FAILURE);
    }

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
