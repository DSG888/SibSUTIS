#ifndef RBTREE_H
#define RBTREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>

#define Printer 1
#define COLOR_RED 0
#define COLOR_BLACK 1

//struct rbtree EmptyNode = {0, 0, COLOR_BLACK, NULL, NULL, NULL};
//struct rbtree *NullNode = &EmptyNode;

struct rbtree *rbtree_add(struct rbtree *root, int key, char *value);
struct rbtree *rbtree_lookup(struct rbtree *root, int key);
void rbtree_free(struct rbtree *root);
struct rbtree *rbtree_min(struct rbtree *root);
struct rbtree *rbtree_max(struct rbtree *root);
struct rbtree *rbtree_delete(struct rbtree *root, int key);
void graph_color_print (struct rbtree *root, FILE *inputfile);
//void rbtree_print_dfs(struct rbtree *root, int level);
void rbtree_print_dfs(struct rbtree *root, int level, char *filename);

#endif
