#include "fibheap.h"

struct heap* CreateFibHeap()	//O(1)
{
	struct heap* H = (struct heap* )malloc(sizeof(struct heap));
	H->min = NULL;
	H->n = 0;
	return H;
}

struct node* CreateFibHeapNode (int k)	//O(1)
{
	struct node* x = (struct node* )malloc(sizeof(struct node));
	x->key = k;
	x->degree = 0;
	x->p = NULL;
	x->child = NULL;
	x->mark = False;
	return x;
}

void FibHeapInsert (struct heap* H, struct node* x)	//O(1)
{
	if(H->min)
	{
	 	H->min->right->left = x;
	 	x->left = H->min;
	 	x->right = H->min->right;
		H->min->right = x;
		if (x->key < H->min->key)
		{
			H->min = x;
		}
	 }
	 else
	 {
	 	x->left = x;
		x->right = x;
	 	H->min = x;
	 }
	 H->n++;
}

struct node* FibHeapMin (struct heap* H)	//O(1)
{
	return H->min;;
}

struct heap* FibHeapUnion (struct heap* H1, struct heap* H2)	//O(1)
{
	struct heap* H = CreateFibHeap();
	if (H1->min&&H2->min)
	{
		H->min = H1->min;
		H->min->left->right = H2->min->right;		// объединение списков
		H2->min->right->left = H->min->left;
		H->min->left = H2->min;
		H2->min->right = H->min;
		if ((H1->min == NULL) || ((H2->min) && (H2->min->key <= H1->min->key)))
		{
		   H->min = H2->min;
		}
	}
	else
		if (H1->min)
		{
			H->min = H1->min;
		}
		else
			if (H2->min)
			{
				H->min = H2->min;
			}
	H->n = H1->n + H2->n;
	return H;
}

struct node* DeleteMin (struct heap* H)	//O(log n)
{
	struct node* z = H->min;
	if (z)
	{
		// z - единственный в списке корней
		if (z == z->right)
		{
			// помечаем указатель на ноль или ребенка
			H->min = z->child;
			Consolidate(H);
		}
		else
		{
			if (z->child == NULL)
			{
				// удаляем z из списка корней
				z->left->right = z->right;
				z->right->left = z->left;
				H->min = z->right;
				Consolidate(H);
			}
			else
			{
				// удаляем z из списка корней
				z->left->right = z->child;
				z->right->left = z->child->left;
				z->child->left->right = z->right;
				z->child->left = z->left;
				H->min = z->right;
				Consolidate(H);
			}
		}
		H->n--;
	}
	return z;
}

void Consolidate(struct heap* H)	//O(log n)
{
	int Dn = (int)(log10(H->n - 1)/log10(2));
	int i;
	struct node** A = (struct node**)malloc(Dn*sizeof(struct node*));
	for (i=0; i<=Dn; i++)
	{
		A[i] = NULL;
	}
	struct node* w = H->min;
	struct node* tmp = NULL;
	struct node* x = NULL;
	struct node* y = NULL;
	struct node* buf = NULL;
	int d, num = 0, k = 0;
	if (H->min)
	{
		num++;
		while (w != H->min->left)
		{
			num++;
			buf = w->right;
			w = buf;
		}
	}
	w = H->min;
	for (; k < num; k++)
	{
		x = w;
		d = x->degree;
		while (A[d])
		{
			y = A[d];
			if (x->key > y->key)
			{
				buf = x;
				x = y;
				y = buf;
			}
			Fib_Heap_Link(H, y, x);
			A[d] = NULL;
			d++;
		}
		A[d] = x;
		tmp = x->right;
		w = tmp;
	}
	H->min = NULL;
	for (i=0; i<=Dn; i++)
	{
		if (A[i])
		{
			if ((H->min == NULL) || (A[i]->key < H->min->key))
			{
				H->min = A[i];
				//H->min->left->right = A[i];		// не обязательно
				//A[i]->left = H->min->left;		// не обязательно
				//A[i]->right = H->min;				// не обязательно
				//H->min->left = A[i];				// не обязательно
			}
		}
	}
}

void Fib_Heap_Link(struct heap* H, struct node* y, struct node* x)	//O(1)
{
	y->left->right = y->right;
	y->right->left = y->left;
	y->p = x;
	y->right = y;
	y->left = y;
	if (x->child)
	{
		y->right = x->child->right;
		y->left = x->child;
		x->child->right->left = y;
		x->child->right = y;
	}
	x->child = y;
	x->degree++;
	y->mark = False;
}

void DecreaseKey (struct heap* H, struct node* x, int k)
{
	if (k > x->key)
	{
		printf ("Error! New key is bigger than current\n");
	}
	else
	{
		x->key = k;
		struct node* y = x->p;
		if (y && (x->key < y->key))
		{
			Cut(H, x, y);
			Cascading_Cut(H,y);
		}
		if(x->key < H->min->key)
		{
			H->min = x;
		}
	}
}

void Cut (struct heap* H, struct node* x, struct node* y)
{
	if (x == x->right)
	{
		y->child = NULL;					// удаление x из списка дочерних узлов y
	}
	else
	{
		x->left->right = x->right;			// удаление x из списка дочерних узлов y
		x->right->left = x->left;
	}
	y->degree--;							// уменьшение степени (количества дочерних узлов) y
	H->min->right->left = x;				// добавление x в список корней H
	x->right = H->min->right;
	x->left = H->min;
	H->min->right = x;
	x->p = NULL;
	x->mark = False;
}

void Cascading_Cut (struct heap* H, struct node* y)
{
	struct node* z = y->p;
	if (z)
	{
		if (y->mark == False)
		{
			y->mark = True;
		}
		else
		{
			Cut (H, y, z);
			Cascading_Cut(H,z);
		}
	}
}

void Fib_Heap_Delete (struct heap* H, struct node* x)
{
	DecreaseKey(H, x, -2147483647);
	struct node* y = DeleteMin(H);
}

void Print_Fib_Heap (struct heap* H, struct node* x)
{
	struct node* y = x;
	struct node* buf = NULL;
	while (buf != y){
		printf("Узел с приоритетом [%d]\n", x->key);
		if (x->child)
		{
			printf("> %d >\n", x->key);
			Print_Fib_Heap(H, x->child);
			printf("< %d <\n", x->key);
			printf("\n");
		}
		buf = x->right;						// движение по списку корней вправо
		x = buf;
	}
}
