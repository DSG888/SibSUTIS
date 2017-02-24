#ifndef STACK_H
#define	STACK_H

#include "linkedlist.h"

class Stack : protected LinkedList
{
	public:
		Stack();
		
		void push(const int);
		void pop();
};

#endif

