#include <stdio.h>
#include <string.h>
#include "aatree.h"
#include "bstree.h"
#include "rbtree.h"
#include "visual.h"
#include "tester.h"

int Menu()
{
	int req = 0;
	printf(" +------------------------+\n");
	printf(" ! 1. Добавление\t  !\n");
	printf(" ! 2. Массовое добавление !\n");
	printf(" ! 3. Удаление\t\t  !\n");
	printf(" ! 4. Массовое удаление   !\n");
	printf(" ! 0. Выход\t\t  !\n");
	printf(" +------------------------+\n");
	scanf("%d", &req);
	if ((0 > req) | (4 < req))
		req = 0;
	return req;
}

int main(int argc, char *argv[])
{
	int expSet[] = {10000, 25000, 50000, 75000, 100000, 125000, 500000, 1000000, 2250000, 5000000, 10000000, 20000000, 30000000, 40000000, 50000000, 60000000, 70000000, 80000000, 90000000, 100000000};
	int expSetCount = sizeof(expSet) / sizeof(expSet[0]);
	int expcounter, i, Req = -1, counter;
	tresults expresults[expSetCount];

	struct bstreenode *mybstree = NULL;
	struct rbtree *myrbtree = NULL;
	AATree *myaatree = new_aatree();



	if ((2 == argc) && (!(strcmp("-i", argv[1]))))
	{
		if (system("rm AA_* RB_* BS_*"));
		counter = 0;
		Req = Menu();
		while (Req)
		{
			switch(Req)
			{
				case 1:
				{
					int q;
					printf("Вставляемый элемент: ");
					scanf("%d", &q);
					if (search(mybstree, q))
					{
						printf("Узел уже есть\n");
						break;
					}
					char buffer [10];
					char s0[80] = "-ADD";
					mitoa(q, buffer);
					strcat(s0, buffer);
					char s1[80] = {'\0'};
					char s2[80] = "BS_";
					char s3[80] = "RB_";
					char s4[80] = "AA_";
					mitoa(counter, buffer);
					strcat(s1, buffer);
					strcat(s1, s0);
					strcat(s2, s1);
					strcat(s3, s1);
					strcat(s4, s1);
					mybstree = insert(mybstree, q);
					myrbtree = rbtree_add(myrbtree, q);
					aa_insert(myaatree, q);
					bstree_print_dfs(mybstree, s2);
					rbtree_print_dfs(myrbtree, s3);
					aatree_print_dfs((struct aanode_ *)myaatree->root, s4, myaatree->nullnode);
					counter++;
					break;
				}
				case 2:
				{
					int q;
					int mas[1000];
					printf("Число вставляемых элементов: ");
					scanf("%d", &q);
					if (1000 < q)
						q = 1000;
					for (i = 0; i < q; ++i)
					{
						printf(" [%d]: ", i + 1);
						scanf("%d", &mas[i]);
					}
					for (i = 0; q > i; ++i)
					{
						if (search(mybstree, mas[i]))
						{
							printf("Узел уже есть\n");
							continue;
						}
						char buffer [10];
						char s0[80] = "-ADD";
						mitoa(mas[i], buffer);
						strcat(s0, buffer);
						char s1[80] = {'\0'};
						char s2[80] = "BS_";
						char s3[80] = "RB_";
						char s4[80] = "AA_";
						mitoa(counter, buffer);
						strcat(s1, buffer);
						strcat(s1, s0);
						strcat(s2, s1);
						strcat(s3, s1);
						strcat(s4, s1);
						mybstree = insert(mybstree, mas[i]);
						myrbtree = rbtree_add(myrbtree, mas[i]);
						aa_insert(myaatree, mas[i]);
						bstree_print_dfs(mybstree, s2);
						rbtree_print_dfs(myrbtree, s3);
						aatree_print_dfs((struct aanode_ *)myaatree->root, s4, myaatree->nullnode);
						counter++;
					}
					break;
				}
				case 3:
				{
					int q;
					printf("Удаляемый элемент: ");
					scanf("%d", &q);
					char buffer [10];
					char s0[80] = "-DEL";
					mitoa(q, buffer);
					strcat(s0, buffer);
					char s1[80] = {'\0'};
					char s2[80] = "BS_";
					char s3[80] = "RB_";
					char s4[80] = "AA_";
					mitoa(counter, buffer);
					strcat(s1, buffer);
					strcat(s1, s0);
					strcat(s2, s1);
					strcat(s3, s1);
					strcat(s4, s1);
					mybstree = deleteNode(mybstree, q);
					myrbtree = rbtree_delete(myrbtree, q);
					aa_remove(myaatree, q);
					bstree_print_dfs(mybstree, s2);
					rbtree_print_dfs(myrbtree, s3);
					aatree_print_dfs((struct aanode_ *)myaatree->root, s4, myaatree->nullnode);
					counter++;
					break;
				}
				case 4:
				{
					int q;
					int mas[1000];
					printf("Число удаляемых элементов: ");
					scanf("%d", &q);
					if (1000 < q)
						q = 1000;
					for (i = 0; i < q; ++i)
					{
						printf(" [%d]: ", i + 1);
						scanf("%d", &mas[i]);
					}
					for (i = 0; q > i; ++i)
					{
						char buffer [10];
						char s0[80] = "-DEL";
						mitoa(mas[i], buffer);
						strcat(s0, buffer);
						char s1[80] = {'\0'};
						char s2[80] = "BS_";
						char s3[80] = "RB_";
						char s4[80] = "AA_";
						mitoa(counter, buffer);
						strcat(s1, buffer);
						strcat(s1, s0);
						strcat(s2, s1);
						strcat(s3, s1);
						strcat(s4, s1);
						mybstree = deleteNode(mybstree, mas[i]);
						myrbtree = rbtree_delete(myrbtree, mas[i]);
						aa_remove(myaatree, mas[i]);
						bstree_print_dfs(mybstree, s2);
						rbtree_print_dfs(myrbtree, s3);
						aatree_print_dfs((struct aanode_ *)myaatree->root, s4, myaatree->nullnode);
						counter++;
					}
					break;
				}
				case 0:
					return 0;
			}
			
			Req = Menu();
		}
		return 0;
	}
	else
	{
		printf("\"Раскачка\" процессора\n");	// Без нагрузки процессоры intel работают на пониженной частоте, что искажает результаты
		int *tmp = getrandmas(15000000);
		free(tmp);
		
		for (expcounter = 0; expcounter < expSetCount; ++expcounter)
		{
			printf("Тестирование структур на %d элементов\n", expSet[expcounter]);
			printf(" Тестирование на случайном массиве\n");
			printf("  Создание массива случайных чисел (без повторений)\n");
			double tim = wtime();
			int *mas1 = getrandmas(expSet[expcounter]), *mas2;
			printf("  Первый массив создан за %f сек.\n", tim = wtime() - tim);
			printf("  Заполняется бинарное дерево\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; i++)
			{
				mybstree = insert(mybstree, mas1[i]);
			}
			expresults[expcounter].BSTreeFRand = wtime() - tim;
			printf("  Заполняется красно-черное дерево\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; ++i)
			{
				myrbtree = rbtree_add(myrbtree, mas1[i]);
			}
			expresults[expcounter].RBTreeFRand = wtime() - tim;
			printf("  Заполняется AA-дерево\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; i++)
			{
				aa_insert(myaatree, mas1[i]);
			}
			expresults[expcounter].AATreeFRand = wtime() - tim;
			free(mas1);
			printf("  Создание другого случайного массива с теми же значениями\n");
			tim = wtime();
			mas2 = getrandmas(expSet[expcounter]);
			printf("  Второй массив создан за %f сек.\n", tim = wtime() - tim);
			
			printf("  Поиск в бинарном дереве\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; ++i)
			{
				if (!(search(mybstree, mas2[i])))
				{
					printf("Не найден!!!\n");
					exit(1);
				}
			}
			expresults[expcounter].BSTreeSRand = wtime() - tim;
			printf("  Поиск в красно-черном дереве\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; ++i)
			{
				if (NullNode == (rbtree_lookup(myrbtree, mas2[i])))
				{
					printf("Не найден!!!\n");
					exit(1);
				}
			}
			expresults[expcounter].RBTreeSRand = wtime() - tim;
			printf("  Поиск в AA-дереве\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; ++i)
			{
				if (NULL==(aa_search(myaatree, mas2[i])))
				{
					printf("Не найден!!!\n");
					exit(1);
				}
			}
			expresults[expcounter].AATreeSRand = wtime() - tim;
			printf("  Удаление из бинарного дерева\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; i++)
			{
				mybstree = deleteNode(mybstree, mas2[i]);
			}
			expresults[expcounter].BSTreeRRand = wtime() - tim;
			printf("  Удаление из красно-черного дерева\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; i++)
			{
				myrbtree = rbtree_delete(myrbtree, mas2[i]);
			}
			expresults[expcounter].RBTreeRRand = wtime() - tim;
			printf("  Удаление из AA дерева\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; ++i)
			{
				aa_remove(myaatree, mas2[i]);
			}
			expresults[expcounter].AATreeRRand = wtime() - tim;
			printf(" Тестирование на упорядоченном массиве\n");
			if (125000 < expSet[expcounter])
			{
				printf("  Заполнение бинарного дерева пропущено\n");
				expresults[expcounter].BSTreeFSort = -1;
			}
			else
			{
				printf("  Заполняется бинарное дерево\n");
				tim = wtime();
				for (i = 0; i < expSet[expcounter]; ++i)
				{
					mybstree = insert(mybstree, i);
				}
				expresults[expcounter].BSTreeFSort = wtime() - tim;
			}
			printf("  Заполняется красно-черное дерево\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; i++)
			{
				myrbtree = rbtree_add(myrbtree, i);
			}
			expresults[expcounter].RBTreeFSort = wtime() - tim;
			printf("  Заполняется AA-дерево\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; ++i)
			{
				aa_insert(myaatree, i);
			}
			expresults[expcounter].AATreeFSort = wtime() - tim;
			if (125000 < expSet[expcounter])
			{
				printf("  Поиск в бинарном дереве пропущен\n");
				expresults[expcounter].BSTreeSSort = -1;
			}
			else
			{
				printf("  Поиск в бинарном дереве\n");
				tim = wtime();
				for (i = 0; i < expSet[expcounter]; ++i)
				{
					if (!(search(mybstree, i)))
					{
						printf("Не найден!!!\n");
						exit(1);
					}
				}
				expresults[expcounter].BSTreeSSort = wtime() - tim;
			}
			printf("  Поиск в красно-черном дереве\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; i++)
			{
				if (NullNode == (rbtree_lookup(myrbtree, i)))
				{
					printf("Не найден!!!\n");
					exit(1);
				}
			}
			expresults[expcounter].RBTreeSSort = wtime() - tim;
			printf("  Поиск в AA-дереве\n");
			tim = wtime();
			for (i = 0; i < expSet[expcounter]; i++)
			{
				if ((aa_search(myaatree, i)) == NULL)
				{
					printf("Не найден!!!\n");
					exit(1);
				}
			}
			expresults[expcounter].AATreeSSort = wtime() - tim;
			if (125000 < expSet[expcounter])
			{
				printf("  Удаление из бинарного дерева пропущено\n");
				expresults[expcounter].BSTreeRSort = -1;
			}
			else
			{
				printf("  Удаление из бинарного дерева\n");
				tim = wtime();
				for (i = expSet[expcounter]; i > 0; --i)
				{
					mybstree = deleteNode(mybstree, i);
				}
				expresults[expcounter].BSTreeRSort = wtime() - tim;
			}
			printf("  Удаление из красно-черного дерева\n");
			tim = wtime();
			for (i = expSet[expcounter]; i > 0; --i)
			{
				myrbtree = rbtree_delete(myrbtree, i);
			}
			expresults[expcounter].RBTreeRSort = wtime() - tim;
			printf("  Удаление из AA дерева\n");
			tim = wtime();
			for (i = expSet[expcounter]; i > 0; --i)
			{
				aa_remove(myaatree, i);
			}
			expresults[expcounter].AATreeRSort = wtime() - tim;
			printf("\n Результаты для %d элементов:\n", expSet[expcounter]);
			printf("\tСлучайные числа:\n");
			printf("\t\t\t\tBSTree\t\tRBTree\t\tAATree:\n");
			printf("\t\tЗаполнение:\t%f\t%f\t%f\n", expresults[expcounter].BSTreeFRand, expresults[expcounter].RBTreeFRand, expresults[expcounter].AATreeFRand);
			printf("\t\tПоиск:\t\t%f\t%f\t%f\n", expresults[expcounter].BSTreeSRand, expresults[expcounter].RBTreeSRand, expresults[expcounter].AATreeSRand);
			printf("\t\tУдаление:\t%f\t%f\t%f\n", expresults[expcounter].BSTreeRRand, expresults[expcounter].RBTreeRRand, expresults[expcounter].AATreeRRand);
			printf("\n\tУпорядоченный массив:\n");
			printf("\t\tЗаполнение:\t%f\t%f\t%f\n", expresults[expcounter].BSTreeFSort, expresults[expcounter].RBTreeFSort, expresults[expcounter].AATreeFSort);
			printf("\t\tПоиск:\t\t%f\t%f\t%f\n", expresults[expcounter].BSTreeSSort, expresults[expcounter].RBTreeSSort, expresults[expcounter].AATreeSSort);
			printf("\t\tУдаление:\t%f\t%f\t%f\n\n\n", expresults[expcounter].BSTreeRSort, expresults[expcounter].RBTreeRSort, expresults[expcounter].AATreeRSort);
		}
		//Выгрузка результатов
		if (system("rm -rf ./results"));
		if (system("mkdir ./results"));
		FILE *pfile;
		
		printf("Запись результатов в ./results/\n");
		//Заполнение
		//Rand
		pfile = fopen("./results/FillingBSTreeRand.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].BSTreeFRand);
		fclose(pfile);
		
		pfile = fopen("./results/FillingRBTreeRand.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].RBTreeFRand);
		fclose(pfile);
		
		pfile = fopen("./results/FillingAATreeRand.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].AATreeFRand);
		fclose(pfile);
		//Sort
		pfile = fopen("./results/FillingBSTreeSort.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			if (0 < expresults[i].BSTreeFSort)
				fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].BSTreeFSort);
		fclose(pfile);
		
		pfile = fopen("./results/FillingRBTreeSort.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].RBTreeFSort);
		fclose(pfile);
		
		pfile = fopen("./results/FillingAATreeSort.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].AATreeFSort);
		fclose(pfile);
		
		//Поиск
		//Rand
		pfile = fopen("./results/SearchBSTreeRand.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].BSTreeSRand);
		fclose(pfile);
		
		pfile = fopen("./results/SearchRBTreeRand.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].RBTreeSRand);
		fclose(pfile);
		
		pfile = fopen("./results/SearchAATreeRand.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].AATreeSRand);
		fclose(pfile);
		//Sort
		pfile = fopen("./results/SearchBSTreeSort.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			if (0 < expresults[i].BSTreeSSort)
				fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].BSTreeSSort);
		fclose(pfile);
		
		pfile = fopen("./results/SearchRBTreeSort.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].RBTreeSSort);
		fclose(pfile);
		
		pfile = fopen("./results/SearchAATreeSort.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].AATreeSSort);
		fclose(pfile);
		
		//Удаление
		//Rand
		pfile = fopen("./results/RemovalBSTreeRand.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].BSTreeRRand);
		fclose(pfile);
		
		pfile = fopen("./results/RemovalRBTreeRand.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].RBTreeRRand);
		fclose(pfile);
		
		pfile = fopen("./results/RemovalAATreeRand.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].AATreeRRand);
		fclose(pfile);
		//Sort
		pfile = fopen("./results/RemovalBSTreeSort.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			if (0 < expresults[i].BSTreeRSort)
				fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].BSTreeRSort);
		fclose(pfile);
		
		pfile = fopen("./results/RemovalRBTreeSort.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].RBTreeRSort);
		fclose(pfile);
		
		pfile = fopen("./results/RemovalAATreeSort.dat", "wt");
		for (i = 0; i < expSetCount; ++i)
			fprintf(pfile, "%d\t%f\n", expSet[i], expresults[i].AATreeRSort);
		fclose(pfile);
	}
	return 0;
}
