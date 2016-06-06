/*
	Требуется реализовать алгоритм Дейкстры поиска кратчайшего пути от заданной вершины до всех
остальных. Для хранения длин кратчайших путей (массив d[i]) следует использовать бинарную кучу
(min-heap). Для хранения графа использовать матрицу смежности.
		Экспериментальное исследование:
	Необходимо сформировать связный граф из 20 вершин и найти в нем кратчайший путь от вершины 1
до всех остальных. Граф и найденные кратчайшие пути включить в отчет.
На экран вывести путь и его длину.

http://graphonline.ru/
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "graph.h"
#include "heap.h"
#include "dijkstra.h"

#define N 20

// Сложна
int mysqrt(int x)
{
	register int op, res, one;
	op = x;
	res = 0;
	one = 1 << 30;	
	while (one > op) one >>= 2;

	while (one != 0)
	{
		if (op >= res + one)
		{
			op = op - (res + one);
			res = res +  2 * one;
		}
		res /= 2;
		one /= 4;
	}
	return(res);
}


// Этот колхоз ужасен. Но это не мешает его сувать в 4ю лабу подряд.
int Read(char *IFILE, int *mas)
{
	char word[100]= {' '};
	uint32_t CountWord = 0, CountSpace = 0;
	FILE* f;
	if((f = fopen(IFILE, "r")) == NULL)
	{
		perror("fopen");
		exit(1);
	}
	register int inWord = 0;
	int c;
	int WLen = 0;
	while((c = getc(f)) != EOF)
	{
		if(isspace(c) || c == '\n')
		{
			inWord = 0;
			++CountSpace;
			if (WLen)
			{
				word[WLen] = '\0';
				mas[CountWord - 1] = atoi(word);
			}
			WLen = 0;
		}
		else
		{
			word[WLen] = c;
			++WLen;
			if(inWord == 0)
			{
				inWord = 1;
				++CountWord;
			}
		}
	}
	return CountWord;
}

//FIXME
int d[N];
int prev[N];
int path[N];

/*
int *M = (int*)malloc(sizeof(int)*N*N)
M[i*N+j] 
*/

int main()
{
	int Mas[400] = {0};
	int i, j, n, len;
	n = Read("mygraph.text", Mas);
	i = mysqrt(n);
	if (i * i != n)
	{
		printf("\tГраф в файле кривой\n");
		exit(2);
	}
	else
	{
		n = i;
		for (i = 0; i < n; ++i)
		{
			if ((n) < (i))
				break;
			if (Mas[i * n + i] != 0)
			{
				printf("\tАлгоритм Дейкстры не умеет работать с узлами\n");
				exit(3);
			}
		}
	}
		

	struct graph *g;
	g = graph_create (N);
	
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			if (0 < Mas[(i) * n + (j)])
			{
				graph_set_edge(g, (i + 1), (j + 1), Mas[(i) * n + (j)]);
				
				printf(" %d", Mas[(i) * n + (j)]);
			}
			else
				printf("  ∞");
		}
		printf("\n");
	}
	
	ShortestPathDijkstra(g, 1);

	for (i = 1; i <= N; i++)
	{
		len = RecoveryPath (g, 1, i);
		printf(" Длина кратчайшего пути 0 >> %d = %d\n", i, d[i]);
		printf("\tКратчайший путь = ");
		for (j = 1; j < len; j++)
		{
			printf("%d -> ", path[j] - 1);
		}
		printf("%d\n\n", path[j] - 1);
	}
	return 0;
}

