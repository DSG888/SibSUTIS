#include "rbtree.h"

struct rbtree {
	int key;
	char *value;
	int color;
	struct rbtree *parent;
	struct rbtree *left;
	struct rbtree *right;
};

struct rbtree EmptyNode = {0, 0, COLOR_BLACK, NULL, NULL, NULL};
struct rbtree *NullNode = &EmptyNode;

struct rbtree *rbtree_left_rotate(struct rbtree *root, struct rbtree *node)
{
	if (Printer)
		printf("    Левый поворот\n");
	struct rbtree *right = node->right;
	/* Create node->right link */
	node->right = right->left;
	if (right->left != NullNode)
		right->left->parent = node;
	/* Create right->parent link */
	if (right != NullNode)
		right->parent = node->parent;
	if (node->parent != NullNode)
	{
		if (node == node->parent->left)
			node->parent->left = right;
		else
			node->parent->right = right;
	}
	else
	{
		root = right;
	}
	right->left = node;
	if (node != NullNode)
		node->parent = right;
	return root;
}

struct rbtree *rbtree_right_rotate(struct rbtree *root, struct rbtree *node)
{
	if (Printer)
		printf("    Правый поворот\n");
	struct rbtree *left = node->left;
	/* Create node->left link */
	node->left = left->right;
	if (left->right != NullNode)
		left->right->parent = node;
	/* Create left->parent link */
	if (left != NullNode)
		left->parent = node->parent;
	if (node->parent != NullNode)
	{
		if (node == node->parent->right)
			node->parent->right = left;
		else
			node->parent->left = left;
	}
	else
	{
		root = left;
	}
	left->right = node;
	if (node != NullNode)
		node->parent = left;
	return root;
}

struct rbtree *rbtree_fixup_add(struct rbtree *root, struct rbtree *node)
{
	struct rbtree *uncle;
	/* Current node is RED */
	while (node != root &&
	node->parent->color == COLOR_RED)
	{
		if (node->parent == node->parent->parent->left)
		{
			/* Node in left tree of grandfather */
			uncle = node->parent->parent->right;
			if (uncle->color == COLOR_RED)
			{
				/* Case 1 - uncle is RED */
				node->parent->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				node->parent->parent->color = COLOR_RED;
				node = node->parent->parent;
				if (Printer)
					printf("    Изменение цветов\n");
			}
			else
			{
				/* Cases 2 & 3 - uncle is BLACK */
				if (node == node->parent->right)
				{
					/* Reduce case 2 to case 3 */
					node = node->parent;
					root = rbtree_left_rotate(root, node);
				}
				/* Case 3 */
				node->parent->color = COLOR_BLACK;
				node->parent->parent->color = COLOR_RED;
				root = rbtree_right_rotate(root, node->parent->parent);
				if (Printer)
					printf("    Изменение цветов\n");
			}
		}
		else
		{
			/*
			* Node in right tree of grandfather
			*
			* Cases 4, 5, 6 - node in right tree
			* of grandfather
			*/
			uncle = node->parent->parent->left;
			if (uncle->color == COLOR_RED)
			{
				/* Uncle is RED – case 4 */
				node->parent->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				node->parent->parent->color = COLOR_RED;
				node = node->parent->parent;
				if (Printer)
					printf("    Изменение цветов\n");
			}
			else
			{
				/* Uncle is BLACK */
				if (node == node->parent->left)
				{
					node = node->parent;
					root = rbtree_right_rotate(root, node);
				}
				node->parent->color = COLOR_BLACK;
				node->parent->parent->color = COLOR_RED;
				root = rbtree_left_rotate(root,
				node->parent->parent);
				if (Printer)
					printf("    Изменение цветов\n");
			}
		}
	}
	root->color = COLOR_BLACK;
	return root;
}

struct rbtree *rbtree_add(struct rbtree *root, int key, char *value)
{
	struct rbtree *node, *parent = NullNode;
	/* Search leaf for new element */
	for (node = root; node != NullNode && node != NULL;)
	{
		parent = node;
		if (key < node->key)
			node = node->left;
		else if (key > node->key)
			node = node->right;
		else
			return root;
	}
	node = malloc(sizeof(*node));
	if (node == NULL)
		return NULL;
	node->key = key;
	node->value = value;
	node->color = COLOR_RED;
	node->parent = parent;
	node->left = NullNode;
	node->right = NullNode;
	
	if (parent != NullNode)
	{
		if (key < parent->key)
			parent->left = node;
		else
			parent->right = node;
	}
	else
	{
		root = node;
	}
	return rbtree_fixup_add(root, node);
}

// Поиск Минимального.
struct rbtree *rbtree_min(struct rbtree *root)
{
	if (root == NullNode)
		return NullNode; 
	struct rbtree *min = root; 
	while (min->left != NullNode)
		min = min->left; 
	return min;
}

// Поиск Максимального
struct rbtree *rbtree_max(struct rbtree *root)
{
	if (root == NullNode)
		return NullNode; 
	struct rbtree *max = root; 
	while (max->right != NullNode)
		max = max->right; 
	return max;
}

// Функция перемещения узлов
// на вход передаем корень и два узла. 
// Функция меняет местами u & v
struct rbtree *rbtree_transplant(struct rbtree *root, struct rbtree *u, struct rbtree *v)
{
	// Если u - корень
	if ((u->parent == NULL) || (u->parent == NullNode))
		root = v;
	else if (u == u->parent->left)	// u - левое поддерево
		u->parent->left = v;
	else
		u->parent->right = v;		// u - правое поддерево 
	v->parent = u->parent;			// Меняем родителя
	return root;
}

// Функция востановления свойств красно-черных деревьев 
// после уаления. На вход подается дерево и узел.
struct rbtree *rbtree_fixup_delete(struct rbtree *root, struct rbtree *x)
{
	struct rbtree *w;
	while ((x != root) && (x->color == COLOR_BLACK))
	{
		if (x == x->parent->left)
		{
			w = x->parent->right;
			if (w->color == COLOR_RED)
			{
				w->color = COLOR_BLACK;
				x->parent->color = COLOR_RED;
				root = rbtree_left_rotate(root, x->parent);
				w = x->parent->right;
			}
			if ((w->left->color == COLOR_BLACK) && (w->right->color == COLOR_BLACK)) {
				w->color = COLOR_RED;
				x = x->parent;
			}
			else
			{
				if (w->right->color == COLOR_BLACK)
				{
					w->left->color = COLOR_BLACK;
					w->color = COLOR_RED;
					root = rbtree_right_rotate(root, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = COLOR_BLACK;
				w->right->color = COLOR_BLACK;
				root = rbtree_left_rotate(root, x->parent);
				x = root;
			}
		}
		else
		{
			w = x->parent->left;
			if (w->color == COLOR_RED)
			{
				w->color = COLOR_BLACK;
				x->parent->color = COLOR_RED;
				root = rbtree_right_rotate(root, x->parent);
				w = x->parent->left;
			}
			if ((w->right->color == COLOR_BLACK) && (w->left->color == COLOR_BLACK))
			{
				w->color = COLOR_RED;
				x = x->parent;
			}
			else
			{
				if (w->left->color == COLOR_BLACK)
				{
					w->right->color = COLOR_BLACK;
					w->color = COLOR_RED;
					root = rbtree_left_rotate(root, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = COLOR_BLACK;
				w->left->color = COLOR_BLACK;
				root = rbtree_right_rotate(root, x->parent);
				x = root;
			}
		}
	}
	x->color = COLOR_BLACK;
	return root;
}

// Удаление узла по ключу. 
struct rbtree *rbtree_delete(struct rbtree *root, int key)
{
	// Ищем удаляемый узел, создаем ссылку и сохраняем цвет
	struct rbtree *z, *y, *x;
	z = rbtree_lookup(root, key);
	if ((z == NULL) || (z == NullNode))
		return root;
	y = z;
	int y_color = y->color;
	if (z->left == NullNode || z->left == NULL)
	{
		// Если у удаляемого элемента нет левого
		x = z->right;
		root = rbtree_transplant(root, z, z->right);
	}
	else
		if (z->right == NullNode || z->right == NULL)
		{
			// Если у удаляемого элемента нет правого
			x = z->left;
			root = rbtree_transplant(root, z, z->left);
		}
		else
		{
			// Если удаляемый узел (z) имеет оба поддерева 
			y = rbtree_min(z->right);
			y_color = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else
			{
				root = rbtree_transplant(root, y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			root = rbtree_transplant(root, z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
	if (y_color == COLOR_BLACK)
		root = rbtree_fixup_delete(root, x);
	free(z);
	return root;
}

// Поиск элемента
struct rbtree *rbtree_lookup(struct rbtree *root, int key)
{
	struct rbtree* search = NullNode;
	// Если дерево пустое
	if (root == NullNode)
		return NullNode; 
	// Если значение совпало
	else 
		if (root->key == key)
			return root; 
	else
		if (root->key > key) 
			search = rbtree_lookup(root->left, key);
	else
		if (root->key < key) 
			search = rbtree_lookup(root->right, key); 
	return search; 
}

// Очистка памяти.int to str in c
void rbtree_free(struct rbtree *root)
{
	// Проверка на пустое дерево
	if (root == NULL || root == NullNode) 
		return; 
	// Рекурсивно запускается очистка 
	if (root->right != NullNode)
		rbtree_free(root->right);
	if (root->left != NullNode)
		rbtree_free(root->left);
	free(root);
}

void rbtree_print_dfs(struct rbtree *root, int level, char *filename )
{
	// Пишем в файл все узлы и связи. 
	void graph_color_print (struct rbtree *root, FILE *inputfile)
	{
		// Пишем ключ
		fprintf(inputfile, "%d", root->key);
		if (root == NullNode)
			return; 
		// Пишем цвет
		if (root->color == COLOR_RED)
		{
			fprintf(inputfile, "[color=red]\n");
		}
		else
			fprintf(inputfile, "[color=black]\n");
		// Пишем рекурсивно вместе с листьями
		if (root->left != NullNode)
		{
			graph_color_print(root->left,inputfile);
			fprintf(inputfile, "%d -> %d\n", root->key, root->left->key);
		}
		else
			fprintf(inputfile, "null[color=black]\n%d -> null\n", root->key);
		if (root->right != NullNode)
		{
			graph_color_print(root->right,inputfile);
			fprintf(inputfile, "%d -> %d\n", root->key, root->right->key);
		}
		else
			fprintf(inputfile, "null[color=black]\n%d -> null\n", root->key);
	}
	
	char s1[80] = "dot -Tpng tree.dot > ";
//	char s2[80] = {'\0'};
	char s3[80] = ".png && rm tree.dot";
	char *name = "tree.dot"; 
	FILE *inputfile = fopen(name, "w");
	
	
	// Готовим файл в формате tree.dot
	fprintf(inputfile, "digraph rbtree {\nnode [style=filled,fontcolor=white]\n");
	// Вызов рекурсивной функции для написания всех узлов
	graph_color_print (root, inputfile);
	fprintf(inputfile, "}");
	fclose(inputfile);
	strcat(s1,filename);
	strcat(s1,s3);
	system(s1);
}

/*
digraph rbtree {
1 [label=24,color=black];
1 -> 5;
1 -> 0;
5 [label=13,color=black];
5 -> 2;
5 -> 7;
2 [label=2,color=red];
7 [label=21,color=red];
0 [label=56,color=red];
0 -> 3;
0 -> 4;
3 [label=29,color=black];
4 [label=71,color=black];
4 -> 6;
6 [label=62,color=red];
}
 
apt-get install graphviz
dot -Tsvg /tmp/1/zz.dot -o outname.svg
*/
