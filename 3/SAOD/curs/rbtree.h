#ifndef RBTREE_H
#define RBTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define COLOR_RED 0
#define COLOR_BLACK 1

//typedef struct node BSTreeNode;
typedef struct rbtree RBTree;

struct rbtree {
	int key;
	int color;
	struct rbtree *parent;
	struct rbtree *left;
	struct rbtree *right;
};

struct rbtree *NullNode;


struct rbtree *rbtree_add(struct rbtree *root, int key);
struct rbtree *rbtree_lookup(struct rbtree *root, int key);
void rbtree_free(struct rbtree *root);
struct rbtree *rbtree_min(struct rbtree *root);
struct rbtree *rbtree_max(struct rbtree *root);
struct rbtree *rbtree_delete(struct rbtree *root, int key);

#endif
