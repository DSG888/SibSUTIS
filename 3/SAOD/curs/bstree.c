#include "bstree.h"
 
 
// A utility function to create a new BST node
struct bstreenode *newNode(int item)
{
    struct bstreenode *temp =  (struct bstreenode *)malloc(sizeof(struct bstreenode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

/* A utility function to insert a new node with given key in BST */
struct bstreenode* insert(struct bstreenode* node, int key)
{
	/* If the tree is empty, return a new node */
	if (node == NULL)
		return newNode(key);
 
	/* Otherwise, recur down the tree */
	if (key < node->key)
		node->left  = insert(node->left, key);
	else
		node->right = insert(node->right, key);

	/* return the (unchanged) node pointer */
	return node;
}
 
/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct bstreenode* minValueNode(struct bstreenode* node)
{
	struct bstreenode* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}
 
/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
struct bstreenode* deleteNode(struct bstreenode* root, int key)
{
	// base case
	if (root == NULL)
		return root;
 
	// If the key to be deleted is smaller than the root's key,
	// then it lies in left subtree
	if (key < root->key)
		root->left = deleteNode(root->left, key);
 
	// If the key to be deleted is greater than the root's key,
	// then it lies in right subtree
	else
		if (key > root->key)
			root->right = deleteNode(root->right, key);

	// if key is same as root's key, then This is the node
	// to be deleted
	else
	{
		// node with only one child or no child
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

		// node with two children: Get the inorder successor (smallest in the right subtree)
		struct bstreenode* temp = minValueNode(root->right);

		// Copy the inorder successor's content to this node
		root->key = temp->key;

		// Delete the inorder successor
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
//		printf("The given data is found in the Binary Search Tree %d\n", rnode->key);
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


/*BSTreeNode* bstreeFind(BSTree tree, int element)
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
*/

/*
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
*/
