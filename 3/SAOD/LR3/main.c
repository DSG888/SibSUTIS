/*
- В файле fibheap.c реализовать функции для работы с Фибоначчиевой кучей (fibonacci heap)
	- Добавление элемента в min-heap
	- Поиск минимального элемента
	- Слияние двух куч
	- Удаление узла с минимальным приоритетом
	- Уменьшение ключа
	- Удаление заданного узла
Контрольные вопросы:
1 Структура Фибоначчиевой кучи
2 Максимальная степень узла в Фибоначчиевой куче
3 Добавление узла
4 Слияние двух куч
5 Алгоритм удаления узла с минимальным приоритетом (уплотнение списка корней – consolidate)
6 Вычислительная сложность операций
*/

//FIXME Добавить функцию удаления заданного узла (обход всей кучи)
//FIXME Добавить в меню функцию уменьшение ключа

#include <stdio.h>
#include "fibheap.h"

int menu()
{
	int req;
	printf("~~~~~~~~~~~~~Куча 1~~~~~~~~~~~~~\n");
	printf(" 1 Вставить узел\n");
	printf(" 2 Получить минимальный узел\n");
	printf(" 3 Удалить минимальный узел\n");
	printf(" 4 Вывод всей кучи\n");
	printf("~~~~~~~~~~~~~Куча 2~~~~~~~~~~~~~\n");
	printf(" 5 Вставить узел\n");
	printf(" 6 Получить минимальный узел\n");
	printf(" 7 Удалить минимальный узел\n");
	printf(" 8 Вывод всей кучи\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf(" 9 Объеденить первую кучу со второй\n");
	printf(" 0 Выход\n");
	scanf("%d", &req);
	return req;
}

int main(int argc, char **argv)
{
	struct node* x;
	struct heap* Heap1 = CreateFibHeap();
	struct heap* Heap2 = CreateFibHeap();
	int req = -1;
	x = NULL;
	printf("\033c");
	while (req)
	{
		printf("\n\n===============================================\n");
		req = menu();
		switch(req)
		{
			int k;
			case 1:
				printf("\033c");
				printf(" Введите приоритет: ");
				scanf("%d", &k);
				x = CreateFibHeapNode(k);
				FibHeapInsert(Heap1, x);
				printf("<Вставлен узел с приоритетом %d>\n", x->key);
				break;
			case 2:
				printf("\033c");
				x = FibHeapMin(Heap1);
				if (x)
					printf("<Узел с минимальным приоритетом - %d>\n", x->key);
				else
					printf("<Куча пустая>\n");
				break;
			case 3:
				printf("\033c");
				x = DeleteMin(Heap1);
				if (x)
				{
					printf("<Удален узел с приоритетом - %d>\n", x->key);
				}
				else
				{
					printf("<Куча уже пуста>\n");
				}
				break;
			case 4:
				printf("\033c");
				if (Heap1->min == NULL)
					printf("<Куча пустая>\n");
				else
				{
					Print_Fib_Heap (Heap1, Heap1->min);
				}
				break;


			case 5:
				printf("\033c");
				printf(" Введите приоритет: ");
				scanf("%d", &k);
				x = CreateFibHeapNode(k);
				FibHeapInsert(Heap2, x);
				printf("<Вставлен узел с приоритетом %d>\n", x->key);
				break;
			case 6:
				printf("\033c");
				x = FibHeapMin(Heap2);
				if (x)
					printf("<Узел с минимальным приоритетом - %d>\n", x->key);
				else
					printf("<Куча пустая>\n");
				break;
			case 7:
				printf("\033c");
				x = DeleteMin(Heap2);
				if (x)
				{
					printf("<Удален узел с приоритетом - %d>\n", x->key);
				}
				else
				{
					printf("<Куча уже пуста>\n");
				}
				break;
			case 8:
				printf("\033c");
				if (Heap2->min == NULL)
					printf("<Куча пустая>\n");
				else
				{
					Print_Fib_Heap (Heap2, Heap2->min);
				}
				break;
			case 9:
				printf("\033c");
				Heap1 = FibHeapUnion(Heap1, Heap2);
				Heap2 = CreateFibHeap();				// FIXME
				break;	
		}
	}
	free(Heap1);	// FIXME
	free(Heap2);	// FIXME
	return 0;
}

//http://www.cs.yorku.ca/~aaw/Jason/FibonacciHeapAnimation.html
