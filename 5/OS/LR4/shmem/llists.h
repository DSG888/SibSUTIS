#ifndef LIST_H
#define LIST_H

#include <stdlib.h>


typedef struct msg_node
{
	int len;
	char *str;
	struct msg_node *next;
} msg_node;


typedef struct list_node
{
	void *npid;
	int num;
	struct list_node *next;
} list_node;


list_node* list_create(void *npid);
list_node* list_insert_end(list_node *list, void *npid);
list_node* list_find_node(list_node *list, list_node *node);
list_node* list_find_by_npid(list_node *list, void *npid);
list_node* list_find(list_node *list, int(*func)(list_node*,void*), void *npid);
void list_remove(list_node **list, list_node *node);
void list_remove_by_npid(list_node **list, void *npid);

#endif
