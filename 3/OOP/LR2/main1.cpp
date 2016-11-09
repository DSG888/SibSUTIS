/*
Задание 1 Написать процедуры и функции для работы со списком
	A. добавление элемента после к-ого элемента списка
	B. удаление из списка к-ого элемента
	C. подсчет числа элементов в списке
	D. перемещение р-ого элемента списка после к-ого элемента
	С. помощью этих процедур и функций создать список следующим образом. 
	* Включать в список полные квадраты из одномерного массива целых чисел (типа Byte). 
	* Удалить повторяющиеся элементы списка. 
	* Определить длину полученного списка.

Задание 2 Написать программу, которая визуально демонстрирует работу стека и очереди. Длина стека и очереди ограничена 10 элементами.
*/

//FIXME Добавить в меню функцию переноса элемента (listnode_move2)

#include <stdio.h>
#include "list.h"

//#include <sys/time.h>

int getrand(int min, int max)
{
	return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

/* reverse:  переворачиваем строку s на месте */
void reverse(char s[])
{
	int i, j;
	char c; 
	for (i = 0, j = strlen(s)-1; i<j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* itoa:  конвертируем n в символы в s */
void mitoa(int n, char s[])
{

	int i, sign; 
	if ((sign = n) < 0)  /* записываем знак */
		n = -n;          /* делаем n положительным числом */
	i = 0;
	do {       /* генерируем цифры в обратном порядке */
		s[i++] = n % 10 + '0';   /* берем следующую цифру */
	} while ((n /= 10) > 0);     /* удаляем */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int menu()
{
	printf("  -= Что сделать с этим списком??? =-\n");
	printf(" 1 Добавить элемент в конец списка\n");
	printf(" 2 Добавить элемент в начало списка\n");
	printf(" 3 Добавить элемент в произвольное место списка\n");
	printf(" 4 Получить значение элемента по порядку\n");
	printf(" 5 Получить строку элемента по значению\n");
	printf(" 6 Удалить элемент по порядку\n");
	printf(" 7 Удалить удалить элемент по значению\n");
	printf(" 8 Получить число элементов в списке\n");
	printf(" 9 Получить число одинаковых элементов в списке\n");
	printf("10 Поменять местами элементы в списке\n");
	printf("11 Убрать повторяющиеся элементы в списке\n");
	printf(" 0 Сломать список и убежать в ужасе\n? ");
	int q;
	scanf("%d", &q);
	return q;
}

int main()
{
	srand (time(NULL));			//initialize random seed
	struct listnode *mylist;
	int mas[20], i;
	for (i = 0; i < 20; i++)
		mas[i] = getrand(1, 16);
	// Создаем список с повторами
	for (i = 0; i < 20; i++)
	{
		char buf[3];
		mitoa(i + 1, buf);
		printf(" Добавлеине в список: %d\n", mas[i]);
		if (!i)
			mylist = listnode_create(mas[i], buf);
		else
			listnode_add(mylist, mas[i], buf);	
	}
	listnode_print(mylist);
	// Чистим повторы
	struct listnode *el;
	int count = listnode_count(mylist);
	int req = -1, req2;

Chistka:	//АЗАЗА GO TO!
	printf("До чистки было элементов: %d\n", count);
	for (i = 0; i < count; i++)
	{
		el = getlistofindex(mylist, i);
		int valtodel = el->val, codel = findallinlist(mylist, valtodel);
		for (; codel > 1; codel--)
		{
			el = listnode_find(mylist, valtodel);
			mylist = listnode_delete_node(mylist, el);
			count--;
		}
	}
	listnode_print(mylist);
//	count = listnode_count(mylist);
	printf("После чистки стало элементов: %d\n", count);
	while (req && req <= 11)
	{
		printf("\n\n\n\n===============================================\n");
		listnode_print(mylist);
		printf("=======================%d======================\n", listnode_count(mylist));
		req = menu();
		switch(req)
		{
			case 1:
				printf("  Добавить число в конец списка: ");
				scanf("%d", &req);
				mylist = listnode_add(mylist ,req, (char *)"U");
				req = -1;
				break;
			case 2:
				printf("  Добавить число в начало списка: ");
				scanf("%d", &req);
				mylist = listnode_addfront(mylist , req, (char *)"U");
				req = -1;
				break;
			case 3:
				printf("  Добавить число: ");
				scanf("%d", &req);
				printf("  Куда?: ");
				scanf("%d", &req2);
				mylist = listnode_add_after(mylist, req, (char *)"U", req2);
				req = -1;
				break;
			case 4:
				printf("  Какой получить?: ");
				scanf("%d", &req);
				el = getlistofindex(mylist, req);
				printf(" Искомый элемент содержит значение: %d и строку: '%s'\n", el->val, el->key);
				req = -1;
				break;
			case 5:
				printf("  Какое значение?: ");
				scanf("%d", &req);
				el = listnode_find(mylist, req);
				if (el == NULL)
					printf(" А такого нету!");
				else
					printf(" Строка: '%s'\n", el->key);
				req = -1;
				break;
			case 6:
				printf("  Какой по счету элемент удалить? (0 грохнит список, это голова): ");
				scanf("%d", &req);
				mylist = listnode_delete(mylist, req);
				req = -1;
				break;
			case 7:
				printf("  С каким значением элемент удалить?: ");
				scanf("%d", &req);
				// Поиск первого нужного узла
				el = listnode_find(mylist, req);
				// Удаление этого узла
				if (el == NULL)
					printf(" А такого нету!");
				else
					mylist = listnode_delete_node(mylist, el);
				req = -1;
				break;
			case 8:
				printf("Элементов в списке: %d\n", listnode_count(mylist));
				break;
			case 9:
				printf("  Число элементов с каким значением искать будем?: ");
				scanf("%d", &req);
				printf("Элементов в списке: %d\n", findallinlist(mylist, req));
				req = -1;
				break;
			case 10:
				printf("  Какой элемент менять будем?: ");
				scanf("%d", &req);
				printf("  С каким элементом менять будем?: ");
				scanf("%d", &req2);
				mylist = listnode_move(mylist, req, req2);
				req = -1;
				break;
			case 11:
				req = -1;
				goto Chistka;
			case 12:
				printf("  Какой элемент перемещать будем?: ");
				scanf("%d", &req);
				printf("  Куда его деть?: ");
				scanf("%d", &req2);
				mylist = listnode_move2(mylist, req, req2);
				req = -1;
				break;
		}
	}
	return 0;
}
