#ifndef BSTREE_H
#define BSTREE_H

#include <stdlib.h>

struct bstreenode
{
    int key;
    struct bstreenode *left, *right;
};

typedef struct bstreenode BSTree;


struct bstreenode *deleteNode(struct bstreenode* root, int key);
struct bstreenode *minValueNode(struct bstreenode* node);
struct bstreenode *insert(struct bstreenode *node, int key);
struct bstreenode *newNode(int item);
struct bstreenode *search(struct bstreenode *root, int key);

#endif
