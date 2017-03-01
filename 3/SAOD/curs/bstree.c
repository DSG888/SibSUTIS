#include "bstree.h"

struct bstreenode *newNode(int item)
{
    struct bstreenode *temp =  (struct bstreenode *)malloc(sizeof(struct bstreenode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct bstreenode* insert(struct bstreenode* node, int key)
{
	if (node == NULL)
		return newNode(key);
 
	if (key < node->key)
		node->left  = insert(node->left, key);
	else
		node->right = insert(node->right, key);
	return node;
}

struct bstreenode* minValueNode(struct bstreenode* node)
{
	struct bstreenode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

struct bstreenode* deleteNode(struct bstreenode* root, int key)
{
	if (root == NULL)
		return root;

	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else
		if (key > root->key)
			root->right = deleteNode(root->right, key);
	else
	{
		if (root->left == NULL)
		{
			struct bstreenode *temp = root->right;
			free(root);
			return temp;
		}
		else
			if (root->right == NULL)
			{
				struct bstreenode *temp = root->left;
				free(root);
				return temp;
			}

		struct bstreenode* temp = minValueNode(root->right);

		root->key = temp->key;

		root->right = deleteNode(root->right, temp->key);
	}
	return root;
}

struct bstreenode* search(struct bstreenode *root, int key)
{
	struct bstreenode *rnode = root;
	if (rnode == NULL)
	{
		return NULL;
	}
	if (key == rnode->key)
	{
		return rnode;
	}
	if (key < rnode->key)
	{
		rnode = search(rnode->left, key);
	}
	else
	{
		rnode = search(rnode->right, key);
	}
	if (rnode)
		return rnode;
	else
		return 0;
}
