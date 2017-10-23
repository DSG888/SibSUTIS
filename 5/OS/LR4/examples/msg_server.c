#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "msgq.h"

int main () {
    message_t msg;
    key_t key;
    int msgid, n;

    if ((key = ftok("./", 'A')) < 0) {
        fprintf(stderr, "ftok error\n");
        exit(EXIT_FAILURE);
    }

    msg.mtype = 1L;

    if ((msgid = msgget(key, PERM | IPC_CREAT)) < 0) {
        fprintf(stderr, "msgget error\n");
        exit(EXIT_FAILURE);
    }

    n = msgrcv(msgid, &msg, sizeof(message_t), msg.mtype, 0);
    if (n > 0) {
        printf("buf[0-%d] = [%s]\n", n, msg.buf);
    }

    return 0;
}
