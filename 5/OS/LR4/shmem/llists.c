#include "llists.h"

list_node* list_create(void *npid)
{
	list_node *l = malloc(sizeof(list_node));
	if (l != NULL)
	{
		l->next = NULL;
		l->npid = npid;
	}

	return l;
}

list_node* list_insert_end(list_node *list, void *npid)
{
	list_node *new_node = list_create(npid);
	if (new_node != NULL)
	{
		for(list_node *it = list; it != NULL; it = it->next)
		{
			if (it->next == NULL)
			{
				it->next = new_node;
				break;
			}
		}
	}
	return new_node;
}

list_node* list_find_node(list_node *list, list_node *node)
{
	while (list)
	{
		if (list == node) break;
		list = list->next;
	}
	return list;
}

list_node* list_find_by_npid(list_node *list, void *npid)
{
	while (list)
	{
		if (list->npid == npid)
			break;
		list = list->next;
	}
	return list;
}

list_node* list_find(list_node *list, int(*func)(list_node*,void*), void *npid)
{
	if (!func) return NULL;
	while(list)
	{
		if (func(list, npid))
			break;
		list = list->next;
	}
	return list;
}

void list_remove(list_node **list, list_node *node)
{
	list_node *tmp = NULL;
	if (list == NULL || *list == NULL || node == NULL) return;

	if (*list == node)
	{
		*list = (*list)->next;
		free(node);
		node = NULL;
	}
	else
	{
		tmp = *list;
		while (tmp->next && tmp->next != node) tmp = tmp->next;
		if (tmp->next)
		{
			tmp->next = node->next;
			free(node);
			node = NULL;
		}
	}
}

void list_remove_by_npid(list_node **list, void *npid)
{
	if (list == NULL || *list == NULL || npid == NULL)
		return;
	list_remove(list, list_find_by_npid(*list, npid));
}
