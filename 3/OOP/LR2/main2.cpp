/*
Задание 1 Написать процедуры и функции для работы со списком
	A. добавление элемента после к-ого элемента списка
	B. удаление из списка к-ого элемента
	C. подсчет числа элементов в списке
	D. перемещение р-ого элемента списка после к-ого элемента
	С. помощью этих процедур и функций создать список следующим образом. Включать в список полные квадраты из одномерного массива целых чисел (типа Byte). Удалить повторяющиеся элементы списка. Определить длину полученного списка.

Задание 2 Написать программу, которая визуально демонстрирует работу стека и очереди. Длина стека и очереди ограничена 10 элементами.
*/

#include <stdio.h>
#include "stack.h"
#include "queue.h"

int printmenu()
{
	printf("\n -<МЕНЮ>-\n 0 Выход\n");
	printf("Действия со стеком\n");
	printf(" 1 PUSH\n");
	printf(" 2 POP\n");
	printf(" 3 DEL ALL\n");
	printf(" 4 PrintStack\n");
	printf("Действия с очередью\n");
	printf(" 5 PUSH\n");
	printf(" 6 delete\n");
	printf(" 7 peek\n");
	printf(" 8 PrintQueue\n : ");
}

int main()
{
	stack *MyStack = new stack;
	queue q1;
	createstack(*MyStack);
	int req = -1;
	while(req != 0)
	{
		int r;
		printmenu();
		scanf("%d", &req);
		switch(req)
		{
			case 1:
				printf("Вставка элемента в стек: ");
				scanf("%d", &r);
				if (push(*MyStack, r))
					printf("\tALARM! Переполнение!\n");
				printstack(*MyStack);
				break;
			case 2:
				pop(*MyStack, lenstack(*MyStack));
				printstack(*MyStack);
				break;
			case 3:
				sdel(*MyStack);
				printstack(*MyStack);
				break;
			case 4:
				printstack(*MyStack);
				break;
				
				
				
				
			case 5:
				printf("Вставка элемента в очередь: ");
				scanf("%d", &r);
				if(q1.isqueuefull()==0)
					q1.ins(r);
				else
					printf("Очередь забита\n");
				if(q1.isqueueempty()==0)
				{
					q1.show_queue();
				}
				else
				{
					printf("Очередь пуста\n");
				}
				break;
			case 6:
				if(q1.isqueueempty()==0){
					int ele=q1.del();
					printf("Удален эл.:%d\n", ele);
				}
				else{
					printf("Очередь пуста\n");
				}
			if(q1.isqueueempty()==0)
			{
				q1.show_queue();
			}
			else
				{
					printf("Очередь пуста\n");
				}
				break;
			case 7:
				if(q1.isqueueempty()==0)
				{
					int ele=q1.peek();
					printf("peeked эл.:%d\n", ele);
				}
				else{
					printf("Очередь пуста\n");
				}
				break;
			case 8:
				if(q1.isqueueempty()==0)
				{
					q1.show_queue();
				}
				else
				{
					printf("Очередь пуста\n");
				}
				break;
		}
	}
	return 0;
}
