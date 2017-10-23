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
    int msgid, length;

    if ((key = ftok("./", 'A')) < 0) {
        fprintf(stderr, "ftok error\n");
        exit(EXIT_FAILURE);
    }

    msg.mtype = 1L;

    if ((msgid = msgget(key, 0)) < 0) {
        fprintf(stderr, "msgget error\n");
        exit(EXIT_FAILURE);
    }

    if ((length = sprintf(msg.buf,
                          "Hello server\n")) < 0) {
        fprintf(stderr, "sprintf error\n");
        exit(EXIT_FAILURE);
    }

    if (msgsnd(msgid, &msg, length, 0) < 0) {
        fprintf(stderr, "msgsnd error\n");
        exit(EXIT_FAILURE);
    }

    if (msgctl(msgid, IPC_RMID, 0) < 0) {
        fprintf(stderr, "msgctl error\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
