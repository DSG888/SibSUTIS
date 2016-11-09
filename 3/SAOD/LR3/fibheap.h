#include "stdio.h"		// printf
#include "stdlib.h"		// free, malloc
#include "math.h"		// log10
#include <string.h>

#define True 1
#define False 0

struct node {
	int key;			// ключ
	int degree;			// количество дочерних узлов
	struct node* p;		// указатель на родительский узел
	struct node* left;	// указатель на левый сестринский узел
	struct node* right;	// указатель на правый сестринский узел
	struct node* child;	// указатель на один из дочерних узлов
	int mark;			// логическое значение, которое указывает, были ли потери узлом x дочерних узлов, начиная с момента, когда x стал дочерним узлом какого-то другого узла
};

struct heap {
	struct node* min;
	int n;
};

struct heap* CreateFibHeap();										// Создание кучи
struct node* CreateFibHeapNode(int k);								// Создание узла
void FibHeapInsert (struct heap* H, struct node* x);				// Добавление узла в кучу
struct node* FibHeapMin (struct heap* H);							// Поиск минимального узла
struct heap* FibHeapUnion(struct heap* H1, struct heap* H2);		// Слияние фибоначчиевых куч
struct node* DeleteMin (struct heap* H);							// Удаление минимального узла
void Consolidate (struct heap* H);									// Уплотнение списка корней
void Fib_Heap_Link (struct heap* H, struct node* y, struct node* x);
void DecreaseKey (struct heap* H, struct node* x, int k);			// Уменьшение ключа
void Cut (struct heap* H, struct node* x, struct node* y);
void Cascading_Cut (struct heap* H, struct node* y);
void Fib_Heap_Delete (struct heap* H, struct node* x);
void Print_Fib_Heap (struct heap* H, struct node* x);
