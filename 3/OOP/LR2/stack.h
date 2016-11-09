#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

const int mstack_size = 10;

typedef struct {
	int *s;
    public:	int n;
} stack;

void createstack(stack &st);
void sdel(stack &st);
int push(stack &st, int x);
int pop(stack &st, int t);
int printstack(stack &st);
int lenstack(stack &st);

#endif
