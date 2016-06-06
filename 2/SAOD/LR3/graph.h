#ifndef GRAPHHEADER_H
#define GRAPHHEADER_H

#include <stdio.h>
#include <stdlib.h>

struct graph {
	int nvertices;
	int *m;
	int *visited;
};

struct graph *graph_create(int nvertices);
void graph_clear(struct graph *g);
void graph_free(struct graph *g);
void graph_set_edge(struct graph *g, int i, int j, int w);
int graph_get_edge(struct graph *g, int i, int j);

#endif

