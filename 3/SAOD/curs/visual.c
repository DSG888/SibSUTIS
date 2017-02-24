#include "visual.h"


void aatree_print_dfs(struct aanode_ *Eroot, char *filename,  aanode *nullnode )
{
	int i, a=Eroot->level, cos1 = 0, cos2 = 0;
	int** mas = malloc(a * sizeof(int*));
	for (i = 0; i < a; ++i)
	{
		int j, len = (int)pow(3, i) + 1000;
		mas[i] = malloc(len * sizeof(int*));
		for (j = 0; j < len; ++j)
			mas[i][j] = INT_MIN;
	}
	// Пишем в файл все узлы и связи. 
	void aa_graph_out (struct aanode_ *Eroot, FILE *inputfile)
	{
		// Пишем ключ
		fprintf(inputfile, "%d[color=green fontcolor=black label=\"%d <%d>\"]\n", Eroot->key, Eroot->key, Eroot->level);
		if (Eroot == nullnode)
			return;
		++cos1;
		int i, len = 1000 + ((int)pow(3, a - Eroot->level));
		for (i = 0; i < len; ++i)
		{
			if (INT_MIN == mas[a - Eroot->level][i])
			{
				mas[a - Eroot->level][i] = Eroot->key;
				break;
			}
			
		}

		// Пишем рекурсивно вместе с листьями
		if (Eroot->left != nullnode)
		{
			aa_graph_out(Eroot->left,inputfile);
			fprintf(inputfile, "%d -> %d\n", Eroot->key, Eroot->left->key);
		}
		else
			fprintf(inputfile, "n%p[label=null color=gray fontcolor=white]\n%d -> n%p\n", &(Eroot->left), Eroot->key, &(Eroot->left));
		if (Eroot->right != nullnode)
		{
			aa_graph_out(Eroot->right, inputfile);
			fprintf(inputfile, "%d -> %d\n", Eroot->key, Eroot->right->key);
		}
		else
			fprintf(inputfile, "n%p[label=null color=gray fontcolor=white]\n%d -> n%p\n", &(Eroot->right), Eroot->key, &(Eroot->right));
	}
	
	char s1[80] = "dot -Tpng tree.dot > ";
	char s3[80] = ".png && rm tree.dot";
	char *name = "tree.dot"; 
	FILE *inputfile = fopen(name, "w");
	
	
	// Готовим файл в формате tree.dot
	fprintf(inputfile, "digraph rbtree {\nnode [style=filled,fontcolor=white]\n");
	// Вызов рекурсивной функции для написания всех узлов
	aa_graph_out (Eroot, inputfile);
	
	for (i = 0; i < a; ++i)
	{
		int j, len = (int)pow(3, i)+1000;
		fprintf(inputfile, "{rank = same");
		for (j = 0; j < len; ++j)
			if (INT_MIN != mas[i][j])
			{
				fprintf(inputfile, "; %d", mas[i][j]);
				++cos2;
			}
		fprintf(inputfile, "}\n");
	}
	
	fprintf(inputfile, "}");
	fclose(inputfile);
	strcat(s1,filename);
	strcat(s1, s3);
	if (system(s1));
	if (cos1 != cos2)
		printf("ALARM!!!\n");
}





void bstree_print_dfs(BSTree* tree, char *filename)
{
	// Пишем в файл все узлы и связи. 
	void bs_graph_out (BSTree* tree, FILE *inputfile)
	{
		// Пишем ключ
		fprintf(inputfile, "%d[color=blue fontcolor=white]\n", tree->key);
		if (tree == NULL)
			return; 

		// Пишем рекурсивно вместе с листьями
		if (tree->left != NULL)
		{
			bs_graph_out(tree->left, inputfile);
			fprintf(inputfile, "%d -> %d\n", tree->key, tree->left->key);
		}
		else
			fprintf(inputfile, "n%p[label=null color=gray fontcolor=white]\n%d -> n%p\n", &(tree->left), tree->key, &(tree->left));
		if (tree->right != NULL)
		{
			bs_graph_out(tree->right, inputfile);
			fprintf(inputfile, "%d -> %d\n", tree->key, tree->right->key);
		}
		else
			fprintf(inputfile, "n%p[label=null color=gray fontcolor=white]\n%d -> n%p\n", &(tree->right), tree->key, &(tree->right));
	}
	if (tree == NULL)
	{
		return;
	}
	char s1[80] = "dot -Tpng tree.dot > ";
	char s3[80] = ".png && rm tree.dot";
	char *name = "tree.dot"; 
	FILE *inputfile = fopen(name, "w");
	
	
	// Готовим файл в формате tree.dot
	fprintf(inputfile, "digraph bstree {\nnode [style=filled,fontcolor=black]\n");
	// Вызов рекурсивной функции для написания всех узлов
	bs_graph_out (tree, inputfile);
	fprintf(inputfile, "}");
	fclose(inputfile);
	strcat(s1,filename);
	strcat(s1,s3);
	if (system(s1));
}

void rbtree_print_dfs(RBTree *root, char *filename)
{
	// Пишем в файл все узлы и связи. 
	void graph_color_print (RBTree *root, FILE *inputfile)
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
			fprintf(inputfile, "n%p[label=null color=gray fontcolor=white]\n%d -> n%p\n", &(root->left), root->key, &(root->left));
		if (root->right != NullNode)
		{
			graph_color_print(root->right,inputfile);
			fprintf(inputfile, "%d -> %d\n", root->key, root->right->key);
		}
		else
			fprintf(inputfile, "n%p[label=null color=gray fontcolor=white]\n%d -> n%p\n", &(root->right), root->key, &(root->right));
	}
	
	char s1[80] = "dot -Tpng tree.dot > ";
	char s3[80] = ".png && rm tree.dot";
	char *name = "tree.dot"; 
	FILE *inputfile = fopen(name, "w");
	
	
	// Готовим файл в формате tree.dot
	fprintf(inputfile, "digraph rbtree {\nnode [style=filled,fontcolor=white]\n");
	// Вызов рекурсивной функции для написания всех узлов
	graph_color_print (root, inputfile);
	fprintf(inputfile, "}");
	fclose(inputfile);
	strcat(s1, filename);
	strcat(s1, s3);
	if (system(s1));
}
