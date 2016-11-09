#include "list.h"

listnode *listnode_create(int val, char *key)
{
    listnode *p = new listnode;

    if (!p) return NULL;

    p->val = val;
    p->key = new char[strlen(key)];
    p->next = NULL;
    strcpy(p->key, key);

    return p;
}


listnode *listnode_add(listnode *root, int val, char *key)
{
    listnode *node = listnode_create(val, key);
    listnode *p = root;
    if (!node) return NULL;

    // If it's the first listnode
    if (!p)
    {
        return node;
    }

    // If root has already created
    for ( ; p->next != NULL; p = p->next);

    p->next = node;
    return root;
}

listnode *listnode_addfront(listnode *root, int val, char *key)
{
    listnode *node = listnode_create(val, key);
    if (!node) return NULL;
    node->next = root;
    return node;
}

listnode *listnode_add_after(listnode *root, int val, char *key, int k)
{
    if (root == NULL) return listnode_add(root, val, key);
	if (k == 0)
	{
		root = listnode_addfront(root, val, key);
		return root;
	}
	if (k > listnode_count(root))
	{
		cout << "Бовдур!" << endl;
		k = listnode_count(root);
	}
    if (k < 1) return NULL; // wrong index before
    listnode *p = root;
    int i;
    for (i = 1; (i != k) && (p->next != NULL); i++, p = p->next);
    if (i != k)
		return NULL; // wrong index after

    // if next node is null, then we push new node in the end
    if (p->next == NULL)
    {
        return root = listnode_add(root, val, key);
    }
    else
    { // we push node in mid
        listnode *ptemp = p->next;
        listnode *node = listnode_create(val, key);
        if (!node)
			return NULL;
        p->next = node;
        p->next->next = ptemp;
    }
    return root;
}

listnode *listnode_delete(listnode *root, int k)
{
    listnode *p = root;
    listnode *prev, *next;
    if (!p) return NULL;
    if (k < 1) return NULL;

    int i;
    for (i = 1; (i != k) && (p->next != NULL); i++, p = p->next)
        prev = p;

    if (i != k) return NULL;

    if (p == root)
    {
        root = p->next;
        free(p->key);
        free(p);
    }
    else
		if (p->next == NULL)
		{ // end node
			free(p->key);
			free(p);
			prev->next = NULL;
		}
		else
		{ // middle node
			next = p->next;
			free(p->key);
			free(p);
			prev->next = next;
		}
		return root;
}

listnode *listnode_delete_node(listnode *root, listnode *puziko)
{
    listnode *p = root;
    listnode *prev, *next;
    if (!puziko) return NULL;

    for ( ; (p->next != NULL) && (p != puziko); p = p->next)
    {
        prev = p;
    }

    if (p == root)
    {
        root = p->next;
        free(p->key);
        free(p);
    }
    else 
		if (p->next == NULL)
		{ // end node
			free(p->key);
			free(p);
			prev->next = NULL;
		}
		else
		{ // middle node
			next = p->next;
			free(p->key);
			free(p);
			prev->next = next;
		}
    return root;
}


listnode *listnode_move(listnode *root, int k, int p)
{
    if (k == p) return root;

    if (k > p)
    {
        int tmp = p;
        p = k;
        k = tmp;
    }

    if (p > listnode_count(root))
		return NULL;

    listnode *node1 = root, *node2 = root, *prev1, *prev2;

    for (int i = 1; k != i; i++, node1 = node1->next)
    {
        prev1 = node1;
    }
    for (int i = 1; p != i; i++, node2 = node2->next)
    {
        prev2 = node2;
    }

    if (k == 1 && p == 2)
    {
        node1->next = node2->next;
        node2->next = node1;
        root = node2;
    }
    else
		if (k == 1)
		{
			listnode *p = node1->next;
			node1->next = node2->next;
			prev2->next = node1;
			node2->next = p;
			root = node2;
		}
		else
			if ((k + 1) == p)
			{
				node1->next = node2->next;
				prev1->next = node2;
				node2->next = node1;
			}
			else
			{
				listnode *p = node1->next;
				prev1->next = node2;
				prev2->next = node1;
				node1->next = node2->next;
				node2->next = p;
			}
    return root;
}

int listnode_count(listnode *root)
{
    listnode *p = root;
    int count = 0;
    while (p)
    {
        count++;
        p = p->next;
    }
    return count;
}

listnode *listnode_find(listnode *root, int val)
{
    listnode *p = root;

    while (p!= NULL)
    {
        if (p->val == val) return p;
        p = p->next;
    }
    return NULL;
}

void listnode_queue(listnode *root)
{
    if (root->next)
        listnode_queue(root->next);
    cout << root->key << " " << root->val << endl;
}
void listnode_print(listnode *root)
{
    listnode *p = root;
    cout << "";
    int i = 0;
    while (p)
    {
		if (!(i % 5) && i)
			cout << endl;
        cout << i << ": [\"" << p->key << "\" " << p->val << "],\t";
        p = p->next;
        i++;
    }
    cout << "" << endl;
}

listnode *getlistofindex(listnode *root, int k)
{
    listnode *p = root;
    int i = 0;
    while (p && i<k)
    {
		i++;
        p = p->next;
    }	
	if (k == i)
		return p;
	else
		return NULL;
}

int findallinlist(listnode *root, int val)
{
    listnode *p = root;
    int count = 0;
    while (p)
    {
		if (p->val == val)
			count++;
        p = p->next;
    }
    return count;
}

listnode *listnode_move2(listnode *root, int p, int k)
{
	listnode *el = getlistofindex(root, p-1);
	char *buf = new char[10];//AZAZAZA
	int iz;
	if (el == NULL)
		cout << " А такого нету!" << endl;
	else
	{
		root = listnode_add_after(root, el->val, el->key, k);
		root = listnode_delete(root, p);
	}
	return root;
}
