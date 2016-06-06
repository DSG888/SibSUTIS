#include "dijkstra.h"

#define N 20

//FIXME
int d[N];
int prev[N];
int path[N];

void ShortestPathDijkstra (struct graph *g, int  src)
{
	struct heap *h;
	struct heapnode v;
	struct heapnode pos;
	int i, u, w;
	h = heap_create(N);
	for (i = 1; i < N + 1; i++)
	{
		d[i] = INT_MAX;
		prev[i] = -1;
		heap_insert(h, d[i], i);
		if (i + 1 == src)
		{
			i++;
		}
	}
	d[src] = 0;
	prev[src] = -1;
	heap_insert(h, d[src], src);
	for (i = 1; i < N + 1; i++)
	{
		v = heap_extract_min(h);
		g->visited[v.value] = 1;
		for (u = 1; u < N + 1; u++)
		{
			w = graph_get_edge(g, v.value, u);
			if (w == 0 )
				continue;
			if (g->visited[u] > 0)
				continue;
			if ((d[v.value] + w) < d[u])
			{
				d[u] = d[v.value] + w;
				heap_decrease_key(h, u, d[u]);
				prev[u] = v.value;
			}
		}
	}
}

int RecoveryPath (struct graph *g, int  src, int dst)
{
	int i, j, pathlen = 1, k;
	i = dst;
	while (i != src)
	{
		pathlen = pathlen + 1;
		i = prev[i];
	}
	j = 0;
	i = dst;
	while (i != src - 1)
	{
		k = pathlen - j;
		path[k] = i;
		i = prev[i];
		j = j + 1;
	}
	return pathlen;
}

