#ifndef TESTER_H
#define TESTER_H

#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	double BSTreeSRand;
	double BSTreeFRand;
	double BSTreeRRand;
	double RBTreeSRand;
	double RBTreeFRand;
	double RBTreeRRand;
	double AATreeSRand;
	double AATreeFRand;
	double AATreeRRand;
	double BSTreeSSort;
	double BSTreeFSort;
	double BSTreeRSort;
	double RBTreeSSort;
	double RBTreeFSort;
	double RBTreeRSort;
	double AATreeSSort;
	double AATreeFSort;
	double AATreeRSort;
} tresults;

void mitoa(int n, char s[]);
int *getrandmas(int size);
double wtime();

#endif
