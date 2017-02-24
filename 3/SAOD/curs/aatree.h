#ifndef AA_TREE_H__
#define AA_TREE_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct aanode_ {
	int key;
	int level;
	struct aanode_*left, *right;
} aanode;

typedef struct {
   aanode *root;
   aanode *nullnode;
   aanode *last;
} AATree;

AATree* new_aatree();
void  delete_aatree(AATree *t);
void* aa_search(const AATree *t, const int key);
void  aa_insert(AATree *t, const int key);
void  aa_remove(AATree *t, const int key);

#endif
