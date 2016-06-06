#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

struct heapnode
{
	int key;
	int value;
};

struct heap
{
	int maxsize;
	int nnodes;
	int *pos;
	struct heapnode *nodes;
};

struct heap *heap_create(int maxsize);
void heap_free(struct heap *h);
void heap_swap(struct heapnode *a, struct heapnode *b);
struct heapnode *heap_min(struct heap *h);
int heap_insert(struct heap *h, int key, int  value);
struct heapnode heap_extract_min(struct heap *h);
void heap_heapify(struct heap *h, int index);
int heap_decrease_key(struct heap *h, int index, int key);

#endif
