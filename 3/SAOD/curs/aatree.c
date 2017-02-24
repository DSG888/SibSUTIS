#include "aatree.h"

static aanode* new_aanode(const int key, aanode *nullnode)
{
	aanode *n = (aanode*)malloc(sizeof(aanode));
	if(n == NULL)
		return NULL;
	n->key = key;
	n->level  = 1;
	n->left = n->right = nullnode;
	return n;
}

AATree* new_aatree()
{
	AATree *t = (AATree*)malloc(sizeof(AATree));
	if (t == NULL)
		return NULL;
	aanode *nn = (aanode*)malloc(sizeof(aanode));
	if(nn == NULL)
	{
		free(t);
		return NULL;
	}
	nn->level = 0;
	nn->left = nn->right = nn;
	t->root = t->nullnode = nn;
	return t;
}

static void delete_aatree_(AATree *t, aanode *n)
{
	if (n == t->nullnode)
		return;
	if (n->left != t->nullnode)
		delete_aatree_(t, n->left);
	if (n->right != t->nullnode)
		delete_aatree_(t, n->right);
	free(n);
}
void delete_aatree(AATree *t)
{
	delete_aatree_(t, t->root);
	free(t->nullnode);
	free(t);
}

static aanode* aa_skew(aanode *n)
{
	if(n->level != n->left->level)
		return n;
printf("skew(%d)\n", n->key);
	aanode *left = n->left;
	n->left = left->right;
	left->right = n;
	n = left;
	return n;
}

static aanode* aa_split(aanode *n)
{
	if (n->right->right->level != n->level)
		return n;
printf("split(%d)\n", n->key);
	aanode *right = n->right;
	n->right = right->left;
	right->left = n;
	n = right;
	n->level++;
	return n;
}

static aanode* aa_search_(const aanode *nn, aanode *n, const int key)
{
	if(n == nn)
		return NULL;
	if(n->key > key)
		return aa_search_(nn, n->left, key);
	else
		if(n->key < key)
			return aa_search_(nn, n->right, key);
		else
			return n;
}

void* aa_search(const AATree *t, const int key)
{
	return aa_search_(t->nullnode, t->root, key);
}

static aanode* aa_insert_(AATree *t, aanode *n, const int key)
{
	if(n == t->nullnode)
	{
		n = new_aanode(key, t->nullnode);
		return n;
	}
	if(key < n->key)
	{
		n->left = aa_insert_(t, n->left, key);
	}
	else
		if(key > n->key)
		{
			n->right = aa_insert_(t, n->right, key);
		}
		else
			return n;
	n = aa_skew(n);
	n = aa_split(n);
	return n;
}

void aa_insert(AATree *t, const int key)
{
	t->root = aa_insert_(t, t->root, key);
}

static aanode* aa_remove_(AATree *t, aanode *n, const int key)
{
	if(n == t->nullnode)
		return n;
	t->last = n;
	if(key < n->key)
	{
		n->left = aa_remove_(t, n->left, key);
	}
	else
	{
		n->right = aa_remove_(t, n->right, key);
	}

	if (n->left->level < n->level - 1 || n->right->level < n->level - 1)
	{
		n->level--;
		if (n->right->level > n->level)
			n->right->level = n->level;
		n = aa_skew(n);
		n->right = aa_skew(n->right);
		n->right->right = aa_skew(n->right->right);
		n = aa_split(n);
		n->right = aa_split(n->right);
	}
	return n;
}

void aa_remove(AATree *t, const int key)
{
	t->root = aa_remove_(t, t->root, key);
}
