#include "heap.h"

struct heap *heap_create(int maxsize)
{
	struct heap *h;
	h = malloc(sizeof(*h));
	if (h != NULL) {
		h->maxsize = maxsize;
		h->nnodes = 0;
		h->nodes = malloc(sizeof(*h->nodes) * (maxsize + 1));
		h->pos = malloc(sizeof(*h->nodes)*(maxsize + 1));
		if (h->nodes == NULL)
		{
			free(h);
			return NULL;
		}
	}
	return h;
};

void heap_free(struct heap *h)
{
	free(h->nodes);
	free(h->pos);
	free(h);
}

void heap_swap(struct heapnode *a, struct heapnode *b)
{
	struct heapnode temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void pos_swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

struct heapnode *heap_min(struct heap *h)
{
	if (h->nnodes == 0)
		return NULL;
	return &h->nodes[1];
}

int heap_insert(struct heap *h, int key, int  value)
{
	int i;
	if (h->nnodes >= h->maxsize) 
	{
		return -1;
	}
	h->nnodes++;
	h->nodes[h->nnodes].key = key;
	h->nodes[h->nnodes].value = value;
	h->pos[value] = h->nnodes;
	for (i = h->nnodes; (i > 1) && (h->nodes[i].key < h->nodes[i / 2].key); i = i / 2)
	{
		heap_swap(&h->nodes[i], &h->nodes[i / 2]);
		pos_swap(&h->pos[h->nodes[i].value], &h->pos[h->nodes[i / 2].value]);
	}
	return 0;
}

struct heapnode heap_extract_min(struct heap *h)
{
	struct heapnode minnode;
	if (h->nnodes == 0)
		return (struct heapnode){0, -1};
	minnode = h->nodes[1];
	h->nodes[1] = h->nodes[h->nnodes];
	h->nnodes--;
	heap_heapify(h, 1);
	return minnode;
}

void heap_heapify(struct heap *h, int index)
{
	for (;;)
	{
		int left = 2 * index;
		int right = 2 * index + 1;
		int smallest = index;
		if (left <= h->nnodes && h->nodes[left].key < h->nodes[index].key)
		{
			smallest = left;
		}
		if (right <= h->nnodes && h->nodes[right].key < h->nodes[smallest].key)
		{
			smallest = right;
		}
		if (smallest == index)
			break;
		heap_swap(&h->nodes[index], &h->nodes[smallest]);
		pos_swap(&h->pos[h->nodes[index].value], &h->pos[h->nodes[smallest].value]);
		index = smallest;
	}
}

int heap_decrease_key(struct heap *h, int index, int key)
{
	int i;
	if (h->nodes[index].key < key)
		return -1;
	h->nodes[h->pos[index]].key = key;
	for ( ; index > 1; index = index / 2)
	{
		if (h->nodes[index].key < h->nodes[index / 2].key)
		{
			heap_swap(&h->nodes[index], &h->nodes[index / 2]);
			pos_swap(&h->pos[h->nodes[index].value], &h->pos[h->nodes[index / 2].value]);
		}
	}
	return index;
}
