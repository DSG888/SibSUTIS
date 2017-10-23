#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "shmem_msg.h"

#define MSG_HEADER_SIZE sizeof(message_t)

message_t *shmem_send_msg(void *shmem_segment, char *str, int type)
{
    static void *free_ptr = NULL;
    long int len = strlen(str);
    message_t *tmp = free_ptr ?
        (message_t *)free_ptr : (message_t *)(shmem_segment);

    tmp->type = type;
    tmp->size = len + 1;
    strcpy(tmp->payload, str);
    tmp->payload[len] = '\0';
    free_ptr = (void *)tmp + MSG_HEADER_SIZE + len + 1;
    
    return tmp;
}

message_t *shmem_recv_msg(void *shmem_segment)
{
    static void *free_ptr = NULL;
    message_t *tmp = free_ptr ?
        (message_t *)free_ptr : (message_t *)(shmem_segment);

    free_ptr = (void *)tmp + MSG_HEADER_SIZE + tmp->size;
    
    return tmp;
}
