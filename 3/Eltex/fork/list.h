#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct listnode {
    struct listnode *next;
    int key;
    int parent;
    int pid;
} listnode;

listnode *listnode_create(int val, int key);	// Создание списка
listnode *listnode_add(listnode *root, int key, int parent);	// Добавить в конец
void list_del(listnode *list);

#endif
