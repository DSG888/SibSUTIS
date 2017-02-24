#ifndef VISUAL_H
#define VISUAL_H

#include "aatree.h"
#include "bstree.h"
#include "rbtree.h"

#include <string.h>
#include <math.h>
#include <limits.h>

void bstree_print_dfs(BSTree* tree, char *filename);
void rbtree_print_dfs(RBTree *root, char *filename);
void aatree_print_dfs(aanode *Eroot, char *filename, aanode *nullnode );

#endif
