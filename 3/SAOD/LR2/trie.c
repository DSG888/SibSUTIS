#include "trie.h"

struct trie *trie_create()
{
	struct trie *node;
	if ( (node = malloc(sizeof(*node))) == NULL)
		return NULL;
	node->ch = '\0';
	node->value = NULL;
	node->sibling = NULL;
	node->child = NULL;
	return node;
}

char *trie_lookup(struct trie *root, char *key)
{
	struct trie *node, *list;
	for (list = root; *key != '\0'; key++)
	{
		for (node = list; node != NULL; node = node->sibling)
		{
			if (node->ch == *key)
				break;
		}
		if (node != NULL)
			list = node->child;
		else
			return NULL;
	}
	/* Check: Node must be a leaf node! */
	return node->value;
}

struct trie *trie_insert(struct trie *root, char *key, char *value)
{
	struct trie *node, *parent, *list;
	parent = NULL;
	list = root;
	for (; *key != '\0'; key++)
	{
		/* Lookup sibling node */
		for (node = list; node != NULL; node = node->sibling)
		{
			if (node->ch == *key)
				break;
		}
		if (node == NULL)
		{
			/* Node not found. Add new node */
			node = trie_create();
			node->ch = *key;
			node->sibling = list;
			if (parent != NULL)
				parent->child = node;
			else
				root = node;
			list = NULL;
		}
		else
		{
			/* Node found. Move to next level */
			list = node->child;
		}
		parent = node;
	}
	/* Update value in leaf */
	if (node->value != NULL)
		free(node->value);
	node->value = strdup(value);
	return root;
}

struct trie *trie_delete(struct trie *root, char *key)
{
	int found;
	return trie_delete_dfs(root, NULL, key, &found);
}

struct trie *trie_delete_dfs(struct trie *root, struct trie *parent, char *key, int *found)
{
	struct trie *node, *prev = NULL;
	*found = (*key == '\0' && root == NULL) ? 1 : 0;
	if (root == NULL || *key == '\0')
		return root;
	for (node = root; node != NULL; node = node->sibling)
	{
		if (node->ch == *key)
			break;
		prev = node;
	}
	if (node == NULL)
		return root;
	trie_delete_dfs(node->child, node, key + 1, found);
	if (*found > 0 && node->child == NULL)
	{
		/* Delete node */
		if (prev != NULL)
			prev->sibling = node->sibling;
		else
		{
			if (parent != NULL)
			parent->child = node->sibling;
			else
			root = node->sibling;
		}
		free(node->value);
		free(node);
	}
	return root;
}

void trie_print(struct trie *root, int level)
{
	struct trie *node;
	int i;
	for (node = root; node != NULL; node = node->sibling)
	{
		for (i = 0; i < level; i++)
			printf(" ");
		if (node->value != NULL)
			printf("%c (%s)\n", node->ch, node->value);
		else
			printf("%c \n", node->ch);
		if (node->child != NULL)
			trie_print(node->child, level + 1);
	}
}
