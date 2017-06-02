/*
	Доработать программу лабораторной работы №2:  
	– разработать класс СПИСОК;
	– описать производные классы: СТЕК, ОЧЕРЕДЬ
	  
	Использовать технологии С++:
	– перегрузка конструкторов;
	– Исключения;
	– Статические элементы класса;
	– Списки инициализации.
*/

#include "linkedlist.h"
#include <iostream>

using namespace std;

int menu()
{
	cout << endl << endl << "=== список ===" << endl;
	cout << " 1 Доавить в начало" << endl;
	cout << " 2 Доавить в конец" << endl;
	cout << " 3 Получить начальный" << endl;
	cout << " 4 Получить конечный" << endl;
	cout << " 5 Удалить начальный" << endl;
	cout << " 6 Удалить конечный" << endl;
	cout << " 7 Вывод списка" << endl;
	cout << "===  стек  ===" << endl;
	cout << " 8 Доавить в стек (push)" << endl;
	cout << " 9 Получить значение стека" << endl;
	cout << "10 Удалить значение стека (pop)" << endl;
	cout << "11 Вывод стека" << endl;
	cout << "=== очередь ===" << endl;
	cout << "12 Добавить в очередь (add)" << endl;
	cout << "13 Получить значение очереди (get)" << endl;
	cout << "14 Удалить значение очереди (del)" << endl;
	cout << "15 Вывод очереди" << endl << "? ";
	int R;
	cin >> R;
	return R;
}

int main()
{
	LinkedList mylist;
	Stack mystack;
	Queue myqueue;
	
	int req = -1;
	while (req)
	{
		req = menu();
		switch(req)
		{
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case 11:
				break;
			case 12:
				break;
			case 13:
				break;
			case 14:
				break;
			case 15:
				break;



		}
	}
	
/*	LinkedList list1;
	LinkedList list2;
	
	list1.appendNode(5);
	list1.appendNode(6);
	list1.appendNode(15);
	list1.insertNode(2, 0);
	
	cout << "Index Operator: " << list1[1] << endl << endl;
	
	cout << "Size: " << list1.getSize() << endl;
	
	cout << endl << "List 1:" << endl;
	list1.print();
	list1.printReverse();
	
	list1.deleteNode(0);
	
	cout << endl << "List 1 (after delete):" << endl;
	list1.print();
	
	list2.appendNode(10);
	list2 = list1;
	list2.appendNode(7);
	
	cout << endl << "List 2:" << endl;
	list2.print();*/
	
	return 0;
}
