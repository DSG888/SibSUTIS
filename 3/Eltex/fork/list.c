#include "list.h"

listnode *listnode_create(int key, int parent)
{
    listnode *p = malloc(1 * sizeof(listnode));

    if (!p)
		return NULL;

    p->key = key;
    p->parent = parent;
    p->next = NULL;
    p->pid = 0;
    return p;
}


listnode *listnode_add(listnode *root, int key, int parent)
{
    listnode *node = listnode_create(key, parent);
    listnode *p = root;
    if (!node) return NULL;

    if (!p)
    {
        return node;
    }

    for ( ; p->next != NULL; p = p->next);

    p->next = node;
    return root;
}

void list_del(listnode *list)
{
	if (NULL != list)
	{
		if (NULL != list->next)
		{
			list_del(list->next);
		}
		free(list);
	}
}
