
enum {
    MSG_FINALIZE = 0,
    MSG_TXT,
};

typedef struct message_s {
    int type;
    int size;
    char payload[0];
} message_t;

message_t *shmem_send_msg(void *shmem_segment, char *str, int type);
message_t *shmem_recv_msg(void *shmem_segment);
