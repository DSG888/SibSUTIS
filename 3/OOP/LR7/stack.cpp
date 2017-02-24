#include "stack.h"

Stack::Stack()
{
}

void Stack::push(const int d)
{
	insertNode(d, 0);
}

void Stack::pop()
{
	printOne(0);
	deleteNode(0);
}
