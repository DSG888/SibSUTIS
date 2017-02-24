/*** 2-3 Heap Implementation ***/
/*
 *   Shane Saunders
 */
/* This version is implemented using the same pointer structure as a Fibonacci
 * heap; that is, nodes have a parent pointer, and a child pointer which points
 * to a linked list of children constructed from the left and right pointers of
 * nodes.  In this implementation, the child pointer points to the highest
 * dimension child node.
 */
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#if TTHEAP_DUMP
#endif
#include "ttheap.h"



/*** Prototypes of functions only visible within this file. ***/

void tth_meld(ttheap_t *h, ttheap_node_t *tree_list);
int merge(ttheap_node_t **a, ttheap_node_t **b);
void remove_node(ttheap_t *h, ttheap_node_t *cut_node);
void trim_xnode(ttheap_node_t *x);
void add_child(ttheap_node_t *p, ttheap_node_t *c);
void replace_node(ttheap_node_t *old, ttheap_node_t *new);
void swap_trunks(ttheap_node_t *tr_low, ttheap_node_t *tr_high);



/*** Definitions of functions visible outside of this file. ***/

/* tth_alloc() - creates and returns a pointer to a 2-3 heap.  Argument
 * max_nodes specifies the maximum number of nodes the heap can contain.
 */
ttheap_t *tth_alloc(int max_nodes)
{
	ttheap_t *h;
#if TTHEAP_DUMP
printf("init, "); fflush(stdout);
#endif

	/* Create the heap. */
	h = malloc(sizeof(ttheap_t)); 
 
	/* The maximum number of nodes and the maximum number of trees allowed.
	 */
	h->max_nodes = max_nodes; 
	h->max_trees = 0.5 + log(max_nodes+1)/log(2.0);

	/* Allocate space for an array of pointers to trees, and nodes in the heap.
	 * calloc() initialises all array entries to zero, that is, NULL pointers.
	 */
	h->trees = calloc(h->max_trees, sizeof(ttheap_node_t *));
	h->nodes = calloc(max_nodes, sizeof(ttheap_node_t *));

	/* We begin with no nodes in the heap. */
	h->n = 0;

	/* The value of the heap helps to keep track of the maximum rank as nodes
	 * are inserted and deleted.
	 */
	h->value = 0;

	/* For experimental purposes, we keep a count of the number of key
	 * comparisons.
	 */
	h->key_comps = 0;

	return h;
}


/* tth_free() - destroys the heap pointed to by h, freeing up any space that
 * was used by it.
 */
void tth_free(ttheap_t *h)
{
	int i;

#if TTHEAP_DUMP
printf("free, ");  fflush(stdout);
#endif

	for(i = 0; i < h->max_nodes; i++) {
		free(h->nodes[i]);
	}

	free(h->nodes);
	free(h->trees);
	free(h);
	
#if TTHEAP_DUMP
printf("free-exited, ");  fflush(stdout);
#endif
}


/* tth_insert() - creates and inserts new a node representing vertex_no with
 * key k into the heap pointed to by h.
 */
void tth_insert(ttheap_t *h, int vertex_no, long k)
{
	ttheap_node_t *new;

#if TTHEAP_DUMP
printf("insert, ");
 tth_dump(h);
 fflush(stdout);
#endif

	/* Create an initialise the new node.  The parent pointer will be set to
	 * NULL by tth_meld().
	 */
	new = malloc(sizeof(ttheap_node_t));
	new->child = NULL;
	new->left = new->right = NULL;
	new->dim = 0;
	new->vertex_no = vertex_no;
	new->key = k;

	/* Maintain a pointer to vertex_no's new node in the heap. */
	h->nodes[vertex_no] = new;

	/* Meld the new node into the heap. */
	tth_meld(h, new);

	/* Update the heap's node count. */
	h->n++;

#if TTHEAP_DUMP
/* printf("insert-exited, ");  fflush(stdout); */
printf("insert-exited, ");
 tth_dump(h); 
fflush(stdout); 
#endif
}


/* tth_delete_min() - deletes the minimum node from the heap pointed to by h
 * and returns its vertex number.
 */
int tth_delete_min(ttheap_t *h)
{
	ttheap_node_t *min_node, *child, *next;
	long k, k2;
	int r, v, vertex_no;

#if TTHEAP_DUMP
printf("delete_min, ");  fflush(stdout);
#endif

	/* First we determine the maximum rank tree in the heap. */
	v = h->value;
	r = -1;
	while(v) {
		v = v >> 1;
		r++;
	};

	/* Now locate the root node with the smallest key, scanning from the
	 * maximum rank root position, down to rank 0 root position.
	 */
	min_node = h->trees[r];
	k = min_node->key;
	while(r > 0) {
		r--;
		next = h->trees[r];
		if(next) {
			if((k2 = next->key) < k) {
				k = k2;
				min_node = next;
			}
			h->key_comps++;
		}
	}

	/* We remove the minimum node from the heap but keep a pointer to it. */
	r = min_node->dim;
	h->trees[r] = NULL;
	h->value -= (1 << r);
	h->n--;

	/* A nodes child pointer always points to the child with the highest rank,
	 * so child->right is the smallest rank.  For melding the linked list
	 * starting at child->right we terminate the circular link with a NULL
	 * pointer.
	 */
	child = min_node->child;
		if(child) {
		next = child->right;
		next->left = child->right = NULL;
		tth_meld(h, next);
	}

	/* Record the vertex no to return. */
	vertex_no = min_node->vertex_no;

	/* Delete the old minimum node. */
	h->nodes[vertex_no] = NULL;
	free(min_node);

#if TTHEAP_DUMP
printf("delete_min-exited, ");  fflush(stdout);
#endif

	return vertex_no;
}


/* tth_decrease_key() - For the heap pointed to by h, this function decreases
 * the key of the node corresponding to vertex_no to new_value.   No check is
 * made to ensure that new_value is in-fact less than or equal to the current
 * value, so it is up to the user of this function to ensure that this holds.
 */
void tth_decrease_key(ttheap_t *h, int vertex_no, long new_value)
{
	ttheap_node_t *cut_node, *parent;

#if TTHEAP_DUMP
printf("decrease_key on vn = %d, ", vertex_no);  fflush(stdout);
#endif

	/* Obtain a pointer to the decreased node and its parent and child.*/
	cut_node = h->nodes[vertex_no];
	parent = cut_node->parent;
	cut_node->key = new_value;

	/* No reinsertion occurs if the node changed was a root. */
	if(!parent) {
#if TTHEAP_DUMP
printf("decrease_key-exited, ");  fflush(stdout);
#endif
		return;
	}

	/* Now remove the node and its tree and reinsert it. */
	remove_node(h, cut_node);
	cut_node->right = cut_node->left = NULL;
	tth_meld(h, cut_node);

#if TTHEAP_DUMP
printf("decrease_key-exited, ");  fflush(stdout);
#endif

}



/*** Definitions of functions only visible within this file. ***/

/* tth_meld() - melds  the linked list of trees pointed to by *tree_list into
 * the heap pointed to by h.  This function uses the `right' sibling pointer
 * of nodes to traverse the linked list from lower dimension nodes to higher
 * dimension nodes.  It expects the last nodes `right' pointer to be NULL.
 */
void tth_meld(ttheap_t *h, ttheap_node_t *tree_list)
{
	ttheap_node_t *next, *add_tree;
	ttheap_node_t *carry_tree;
	int d;

#if TTHEAP_DUMP
printf("meld - ");  fflush(stdout);
#endif

	/* add_tree points to the current tree to be merged. */
	add_tree = tree_list;

	carry_tree = NULL;

	do {
		/* add_tree() gets merged into the heap, and also carry_tree if one
		 * exists from a previous merge.
		 */

		/* Keep a pointer to the next tree and remove sibling and parent links
		 * from the current tree.  The dimension of the next tree is always
		 * one greater than the dimension of the previous tree, so this merging
		 * is like an addition of two ternary numbers.
		 *
		 * Note that if add_tree is NULL and the loop has not exited, then
		 * there is only a carry_tree to be merged, so treat it like add_tree.
		 */
		if(add_tree) {
			next = add_tree->right;
			add_tree->right = add_tree->left = add_tree;
			add_tree->parent = NULL;
		}
		else {
			add_tree = carry_tree;
			carry_tree = NULL;
		}

#if TTHEAP_DUMP
printf("%d, ", add_tree->vertex_no);  fflush(stdout);
#endif
 
		/* First we merge add_tree with carry_tree, if there is one.  Note that
		 * carry_tree contains only one node in its main trunk, and add_tree
		 * has at most two, so the result is at most one 3-node trunk, which is
		 * treated as a 1-node main trunk one dimension higher up.
		 */
		if(carry_tree) {
			h->key_comps += merge(&add_tree, &carry_tree);
		}

		/* After the merge, if add_tree is NULL, then the resulting tree
		 * pointed to by carry_tree carries to higher entry, so we do not need
		 * to merge anything into the existing main trunk.
		 * If add_tree is not NULL we add it to the existing main trunk.
		 */
		if(add_tree) {
			d = add_tree->dim;
			if(h->trees[d]) {
				/* Nodes already in this main trunk position, so merge. */
				h->key_comps += merge(&h->trees[d], &add_tree);
				if(!h->trees[d]) h->value -= (1 << d);
				carry_tree = add_tree;
			}
			else {
				/* No nodes in this main trunk position, so use add_tree. */
				h->trees[d] = add_tree;
				h->value += (1 << d);
			}
		}

		/* Obtain a pointer to the next tree to add. */
		add_tree = next;

		/* We continue if there is still a node in the list to be merged, or
		 * a carry tree remains to be merged.
		 */
	} while(add_tree || carry_tree);


#if TTHEAP_DUMP
printf("meld-exited, ");  fflush(stdout);
#endif

}


/* merge() - merges the two trunks pointed to by *a and *b, returning the sum
 * trunk through `a' and any carry tree through `b'.
 * When this function is used, both parameters `a' and `b' refer to either
 * a 1-node or 2-node trunk.
 *
 * Returns the number of key comparisons used.
 */
int merge(ttheap_node_t **a, ttheap_node_t **b)
{
	ttheap_node_t *tree, *next_tree, *other, *next_other;
	int c;

	/* Number of comparisons. */
	c = 0;

	/* `tree' always points to the node with the lowest key.
	 * To begin with, `tree' points to the smaller head node, and `other'
	 * points to the head node of the other trunk.
	 */
	if((*a)->key <= (*b)->key) {
		tree = (*a);
		other = (*b);
	}
	else {
		tree = (*b);
		other = (*a);
	}
	c++;

	/* next_tree points to the next node on the trunk that `tree' is the head
	 * of (if there is another node).
	 * next_other points to the next node on the trunk that `other' is the head
	 * of (if there is another node).
	 */
	next_tree = tree->child;
	if(next_tree && next_tree->dim != other->dim) next_tree = NULL;
	next_other = other->child;
	if(next_other && next_other->dim != other->dim) next_other = NULL;

	/* The merging depends on the existence of nodes and the values of keys. */
	if(!next_tree) {
		/* next_tree does not exist, so we simply make `other' the child of
		 * `tree'. If next_other exist the resulting 3-node trunk is a carry
		 * tree.
		 */

		add_child(tree, other);
		if(next_other) {
			tree->dim++;
			*a = NULL;  *b = tree;
		}
		else {
			*a = tree;  *b = NULL;
		}
	}
	else if(!next_other) {
		/* next_tree exists but next_other does not, so the linked order of
		 * next_tree and `other' in the resulting 3-node trunk depends on the
		 * values of keys.  The resulting 3-node trunk becomes a carry tree.
		 */

		if(next_tree->key <= other->key) {
			add_child(next_tree, other);
		}
		else {
			replace_node(next_tree, other);
			add_child(other, next_tree);
		}
		c++;
		tree->dim++;
		*a = NULL;  *b = tree;
	}
	else {
		/* Otherwise, both next_tree and next_other exist.  The result consists
		 * of a 1 node trunk plus the 3-node trunk which becomes a carry tree.
		 * We two trunks are made up as (tree, other, next_other)
		 * and (next_tree).  This uses no key comparisons.
		 */

		replace_node(next_tree, other);
		next_tree->left = next_tree->right = next_tree;
		next_tree->parent = NULL;
		tree->dim++;
		*a = next_tree;  *b = tree;
	}

	return c;
}


/* remove_node() - removes r_node, and the sub-tree it is the root of, from
 * the heap pointed to by h.  If necessary, this causes rearrangement of
 * r_node's work space.
 */
void remove_node(ttheap_t *h, ttheap_node_t *r_node)
{
	ttheap_node_t *parent, *child, *ax, *bx, *ap, *bp, *b1, *c, *p;
	int d, d1;

	parent = r_node->parent;
	child = r_node->child;
	d = r_node->dim;

	/* If this node is an extra node we simply cut the link between it and its
	 * parent and update its sibling pointers.
	 */
	if(d == parent->dim) {
		trim_xnode(r_node);
	}
	/* Else if its child is an extra node then use its child to replace it. */
	else if(child && child->dim == d) {

		/* First we remove the child. */
		trim_xnode(child);

		/* Now we put the child in r_nodes position. */
		replace_node(r_node, child);

	}
	/* Otherwise we need some rearrangement of the workspace. */
	else {
		
		/* Look at up to two similar nodes in the work space and determine if
		 * they have an extra node under them.  Nodes relative to the node
		 * being removed are pointed to by the pointers ax, ap, bx, and bp.
		 * If a similar trunk lies immediately below cut_node's trunk in the
		 * work space, then either ax or ap will be set to point to the node on
		 * the end of that trunk.  The same applies for bx and bp, but with a
		 * similar trunk immediately above in the work space. the 'x' pointers
		 * are set if there is a 3rd (i.e. extra) node on the trunk.  Otherwise
		 * the 'p' pointer is set to point to the 2nd node.  Pointers will be
		 * set to null if a trunk does not exist or they are not used.
		 */

		/* Check for nodes on a similar trunk above in the work space. */
		p = r_node->parent->left;
		if (p->dim == d) {
			c = p->child;
			if(c && c->dim == d) {
				ax = c;  ap = NULL;
			}
			else {
				ap = p;  ax = NULL;
			}
		}
		else {
			ax = ap = NULL;
		}

		/* Check for nodes on a similar trunk below in the work space. */
		d1 = d + 1;
		p = r_node->right;
		if (p->dim == d1) {
			p = p->child;
			if(p->dim == d1) p = p->left;

			c = p->child;
			if(c && c->dim == d) {
				bx = c;  bp = NULL;
			}
			else {
				bp = p;  bx = NULL;
			}
		}
		else {
			bx = bp = NULL;
		}
		

		if(bx) {

			/* First break `bx's parent link and sibling links. */
			trim_xnode(bx);

			/* Then we insert bx in r_nodes place. */
			replace_node(r_node, bx);
		}
		else if(bp) {

			b1 = bp->parent;

			/* Recursively remove b1. */
			remove_node(h, b1);
			b1->dim = d;

			replace_node(r_node, b1);

			/* It may improve speed by using trim_xnode() when recursion can be
			 * avoided.
			 */
		}
		else if(ax) {

			/* Bend the tree to modify its shape then remove r_node. */
			swap_trunks(ax->parent, parent);
			trim_xnode(r_node);
		}
		else if(ap) {

			/* Bend the tree, so that the node to be relocated, parent, has the
			 * larger key value.
			 */
			if(parent->key < ap->key) {
				swap_trunks(ap, parent);
				p = parent;
				parent = ap;
				ap = p;
			}
			h->key_comps++;

			trim_xnode(r_node);
			remove_node(h, parent);
			parent->dim = d;

			/* Make parent the child of ap. */
			add_child(ap, parent);
		}
		else {
			/* The work space only has r_node node and parent.  This only
			 * occurs when parent is a root node, so after removing r_node we
			 * demote parent to a lower dimension main trunk.
			 */

			/* Note that parent is a root node and has dimension d + 1. */
			h->trees[d+1] = NULL;
			h->value -= (1 << (d+1));

			parent->dim = d;
			trim_xnode(r_node);
			parent->left = parent->right = NULL;

			tth_meld(h, parent);
		}
	}
}


/* trim_xnode() - trims an extra node, x, from its trunk.
 */
void trim_xnode(ttheap_node_t *x)
{
	ttheap_node_t *l, *r;

	if(x->dim == 0) {
		/* A dimension 0 node is an only child, so cutting it leaves no
		 * children.
		 */
		
		x->parent->child = NULL;
	}
	else {
		/* Otherwise, sibling pointers of other child nodes must be updated. */
		
		l = x->left;
		r = x->right;
		l->right = r;
		r->left = l;

		x->parent->child = l;
	}
}


/* swap_trunks() - Where a node in an (i)th trunk, tr_low, and a node in an
 * (i+1)th trunk, tr_high, share the same parent, this function is used for
 * swapping them.
 */
void swap_trunks(ttheap_node_t *tr_low, ttheap_node_t *tr_high)
{
	int d;
	ttheap_node_t *parent, *l, *r;

	/* The dimensions of the two nodes are exchanged. */
	d = tr_low->dim;
	tr_low->dim = tr_high->dim;
	tr_high->dim = d;

	/* Obtain a pointer to the parent of both nodes. */
	parent = tr_high->parent;

	/* If the left sibling of tr_low is not tr_high, we need to update sibling
	 * pointers.  Otherwise, the child pointer of the common parent now
	 * points to tr_low.
	 */
	if((l = tr_low->left) != tr_high) {

		/* Update sibling pointers. */
		r = tr_high->right;
		tr_high->left = l;
		tr_low->right = r;
		tr_high->right = tr_low;
		tr_low->left = tr_high;
		l->right = tr_high;
		r->left = tr_low;

		/* Determine if the child pointer of the common parent will need to be
		 * updated.
		 */
		if(parent->child == tr_high) {
			parent->child = tr_low;
		}
	}
	else {
		parent->child = tr_low;
	}
}


/* add_child() - makes node c and its tree a child of node p.
 */
void add_child(ttheap_node_t *p, ttheap_node_t *c)
{
	ttheap_node_t *l, *r;

	/* If p already has child nodes we must update the sibling pointers.
	 * Otherwise only initialise the left and right pointers of the added
	 * child.
	 */
	if((l = p->child)) {
		r = l->right;
		c->left = l;
		c->right = r;
		r->left = c;
		l->right = c;
	}
	else {
		c->left = c->right = c;
	}

	p->child = c;
	c->parent = p;
}


/* replace_node() - replaces node `old' and its sub-tree with node `new' and
 * its sub-tree.
 */
void replace_node(ttheap_node_t *old, ttheap_node_t *new)
{
	ttheap_node_t *parent, *l, *r;

	l = old->left;
	r = old->right;

	/* If `old' is an only child we only need to initialise the sibling
	 * pointers of the new node.  Otherwise we update sibling pointers of other
	 * child nodes.
	 */
	if(r == old) {
		new->right = new->left = new;
	}
	else {
		l->right = new;
		r->left = new;
		new->left = l;
		new->right = r;
	}

	/* Update parent pointer of the new node and possibly the child pointer
	 * of the parent node.
	 */
	parent = old->parent;
	new->parent = parent;
	if(parent->child == old) parent->child = new;
}



/*** Debugging Functions ***/

/* Recursively print the nodes of a 2-3 heap. */
#if TTHEAP_DUMP
void tth_dump_nodes(ttheap_node_t *ptr, int level)
{
	ttheap_node_t *child_ptr, *partner;
	int i, ch_count;

	 /* Print leading whitespace for this level. */
	for(i = 0; i < level; i++)
		printf("   ");

	printf("%d(%ld)\n", ptr->vertex_no, ptr->key);
	 
	if((child_ptr = ptr->child))
	{
		child_ptr = ptr->child->right;
		 
		ch_count = 0;

		do {
			tth_dump_nodes(child_ptr, level+1);
			if(child_ptr->dim != ch_count)
			{
				for(i = 0; i < level+1; i++)
					printf("   ");
				printf("error(dim)\n");
				exit(1);
			}
			if(child_ptr->parent != ptr)
			{
				for(i = 0; i < level+1; i++)
					printf("   ");
				printf("error(parent)\n");
			}
			if(child_ptr->key < ptr->key)
			{
				for(i = 0; i < level+1; i++)
					printf("   ");
				printf("error(key)\n");
				exit(1);
			}
			child_ptr = child_ptr->right;
			ch_count++;
		} while(child_ptr != ptr->child->right);

		if(ch_count != ptr->dim && ch_count != ptr->dim + 1)
		{
			for(i = 0; i < level; i++)
				printf("   ");
			printf("error(ch_count)\n");
			exit(1);
		}
	}
	else
	{ 
		if(ptr->dim != 0)
		{
			for(i = 0; i < level; i++)
				printf("   ");
			printf("error(dim)\n"); exit(1);
		}
	}
}
#endif

/* Print out a 2-3 heap. */
#if TTHEAP_DUMP
void tth_dump(ttheap_t *h)
{
	int i;
	ttheap_node_t *ptr;

	printf("\n");
	printf("value = %d\n", h->value);
	printf("array entries 0..max_trees =");
	for(i=0; i<h->max_trees; i++)
	{
		printf(" %d", h->trees[i] ? 1 : 0 );
	}
	printf("\n\n");
	for(i=0; i<h->max_trees; i++)
	{
		if((ptr = h->trees[i]))
		{
			printf("tree %d\n\n", i);
			tth_dump_nodes(ptr, 0);
			printf("\n");
		}
	}
	fflush(stdout);
}
#endif


/*** Implement the universal heap structure type ***/

/* 2-3 heap wrapper functions. */

int _tth_delete_min(void *h)
{
	return tth_delete_min((ttheap_t *)h);
}

void _tth_insert(void *h, int v, long k)
{
	tth_insert((ttheap_t *)h, v, k);
}

void _tth_decrease_key(void *h, int v, long k)
{
	tth_decrease_key((ttheap_t *)h, v, k);
}

int _tth_n(void *h)
{
	return ((ttheap_t *)h)->n;
}

long _tth_key_comps(void *h)
{
	return ((ttheap_t *)h)->key_comps;
}

void *_tth_alloc(int n)
{
	return tth_alloc(n);
}

void _tth_free(void *h)
{
	tth_free((ttheap_t *)h);
}

void _tth_dump(void *h)
{
#if TTHEAP_DUMP
	tth_dump((ttheap_t *)h);
#endif
}

/* 2-3 heap info. */
const heap_info_t TTHEAP_info = {
	_tth_delete_min,
	_tth_insert,
	_tth_decrease_key,
	_tth_n,
	_tth_key_comps,
	_tth_alloc,
	_tth_free,
	_tth_dump
};
