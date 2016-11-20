#ifndef BSTREE_H
#define BSTREE_H

#include <stdlib.h>

typedef struct node BSTreeNode;
typedef struct tree BSTree;
typedef struct parent Parent;
//typedef int (*Function)(int);

struct node{
	int data;
	BSTreeNode* left;
	BSTreeNode* right;
	BSTreeNode* parent;
};

struct tree{
	BSTreeNode* root;
};

BSTree createBSTree(void);
BSTreeNode* bstreeCreateNode(int i);
int bstreeInsert(BSTree*, int);
BSTreeNode* bstreeFind(BSTree, int);
void bstreeDeleteNode(BSTree*, int);

#endif
