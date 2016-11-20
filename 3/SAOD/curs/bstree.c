#include "bstree.h"

BSTreeNode* bstreeCreateNode(int i)
{
	BSTreeNode* node = malloc(sizeof(BSTreeNode));
	node->data = i;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return node;
}

BSTree createBSTree(void)
{
	BSTree tree;
	tree.root = NULL;
	return tree;
}

int bstreeInsert(BSTree* tree, int i)
{
	BSTreeNode* node = bstreeCreateNode(i);
	if(tree->root == NULL)
	{
		tree->root = node;
		return 1;
	}
	BSTreeNode* tmp = tree->root;
	BSTreeNode* parent;
	while (tmp != NULL)
	{
		parent = tmp;
		if (i < tmp->data)
			tmp = tmp->left;
		else
			if (i > tmp->data)
				tmp = tmp->right;
//			else
//				return;
	}
	node->parent = parent;
	if (i < parent->data)
		parent->left = node;
	else
		parent->right = node;
}

BSTreeNode* bstreeFind(BSTree tree, int element)
{
	BSTreeNode* node = tree.root;
	if(tree.root->data==element)
	{
		return node;
	}
	else
	{
		if(element>tree.root->data)
		{
			(tree.root->right == NULL)?(node=NULL):(tree.root = tree.root->right);
			(node != NULL) && (node = bstreeFind(tree, element));
		}
		else
		{
			(tree.root->left == NULL)?(node=NULL):(tree.root = tree.root->left);
			(node!=NULL) && (node = bstreeFind(tree, element));	
		}
	}	
	return node;
}

void bstreeDeleteNode(BSTree* tree, int data)
{
	BSTreeNode *node;
	node = bstreeFind(*tree, data);
	if (node->left == NULL && node->right == NULL)
	{
		if (node->parent == NULL)
		{
			tree->root = NULL;
			free(node);
			return;
		}
		(node == node->parent->left) && (node->parent->left = NULL);
		(node == node->parent->right) && (node->parent->right = NULL);
		free(node);
		return;		
	}
	else
	{
		if(node->left != NULL || node->right != NULL)
		{
			if (node == node->parent->left)
			{
				if (node->left != NULL)
				{
					node->left->parent = node->parent;
					node->parent->left = node->left;
				}
				if (node->right != NULL)
				{
					node->right->parent = node->parent;
					node->parent->left = node->right;
				}
			}
			else
			{
				if (node->left != NULL)
				{
					node->left->parent = node->parent;
					node->parent->right = node->left;
				}
				if (node->right != NULL)
				{
					node->right->parent = node->parent;
					node->parent->right = node->right;
				}
			}
			free(node);
			return;	
		}
	}
}
