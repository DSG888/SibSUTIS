#define MAXBUF 80
#define PERM 0666

typedef struct msgbuf_s {
    long mtype;
    char buf[MAXBUF];
} message_t;
