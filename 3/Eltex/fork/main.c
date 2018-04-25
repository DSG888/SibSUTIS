#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int main()
{
	listnode *list = listnode_create(1, 0);
	list->pid = getpid();
	printf("Главный: %d\n", list->pid);
	listnode_add(list, 2, 1);
	listnode_add(list, 3, 1);
	listnode_add(list, 4, 1);
	listnode_add(list, 5, 3);
	listnode_add(list, 6, 4);
	listnode_add(list, 7, 4);

	listnode *tmp;
	
	int th = 1;
	for (tmp = list; tmp->next != NULL; tmp = tmp -> next)
	{
		if (tmp->next->parent == th)
		{
			int old = getpid();
			if (!(fork()))
			{
				tmp -> next -> pid = getpid();
				printf("Я %d [%d], создал процесс %d [%d]\n", old, th, getpid(), tmp->next->key);
				th = tmp->next->key;
			}
		}
	}

//	fork()&&(fork()||fork())&&(fork()||fork());


	if (list->pid != getpid())
		sleep(2);
	else
	{
		system("pstree -p `pidof xfce4-terminal`");
	}
	list_del(list);
	return 0;
}
