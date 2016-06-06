/*
Требуется реализовать на языке C две библиотеки для работы с бинарным деревом
поиска (Binary search tree) и хеш-таблицей (Hash table). Ключом в обоих случаях
является строка (char []), а значением целое число (int).
Функции для работы с бинарным деревом поиска должны быть помещены в файлы
bstree.c (реализация функций) и bstree.h (объявление функций). В файлах необходимо
реализовать следующие функции:
	 struct bstree *bstree_create(char *key, int value)
	 void bstree_add(struct bstree *tree, char *key, int value)
	 struct bstree *bstree_lookup(struct bstree *tree, char *key)
	 struct bstree *bstree_min(struct bstree *tree)
	 struct bstree *bstree_max(struct bstree *tree)
Функции для работы с хеш-таблицей должны быть помещены в файлы hashtab.c
(реализация функций) и hashtab.h (объявление функций). В файлах необходимо
реализовать следующие функции:
	 unsigned int hashtab_hash(char *key)
	 void hashtab_init(struct listnode **hashtab)
	 void hashtab_add(struct listnode **hashtab, char *key, int value)
	 struct listnode *hashtab_lookup(struct listnode **hashtab, char *key)
	 void hashtab_delete(struct listnode **hashtab, char *key)
Цель работы — провести экспериментальное исследование эффективности бинарных
деревьев поиска и хеш-таблиц.

Вариант 3:
	1: Эксперимент 1
	2: Эксперимент 4
	3: Эксперимент 6 - хеш-функции KP, FNV

Эксперимент 1 
Сравнение эффективности поиска элементов в бинарном дереве поиска и хеш-
таблице в среднем случае (average case)
Требуется заполнить таблицу 1 и построить графики зависимости времени t
выполнения операции поиска (lookup) элемента в бинарном дереве поиска и хеш-
таблице от числа n элементов уже вставленных в словарь.
В качестве ключей использовать слова из романа Л.Н. Толстого «Война и Мир»
(можно использовать любой текстовый файл с большим числом слов). Файл включен
в архив.
В качестве искомого ключа следует выбрать случайное слово, которое уже было
добавлено в словарь.

На выходе таблица:
№ 1-20 | Количество элементов в словаре | Время выполнения функции bstree_lookup, с | Время выполнения функции hashtab_lookup, с


Эксперимент 4
Исследование эффективности поиска минимального элемента
в бинарном дереве поиска в худшем и среднем случаях
Требуется заполнить таблицу 4 и построить графики зависимости времени t
выполнения операции поиска минимального элемента в бинарном дереве поиска в
худшем и среднем случаях.
Анализ поведения в худшем случае: добавляем в словарь n слов - от больших к
меньшим (например, слова «zzzzzzzz», «yyyyyy», ...) и замеряем время поиска
минимального ключа.
Анализ поведения в среднем случае: добавляем в словарь n слов и замеряем время
поиска минимального ключа.

На выходе таблица:
№ 1-20 | Количество элементов в словаре | Время выполнения функции bstree_min в худшем случае, с | Время выполнения функции bstree_min в среднем случае, с


Эксперимент 6
Анализ эффективности хеш-функций
Требуется заполнить таблицу 6 и построить:
	 графики зависимости времени t выполнения операции поиска элемента
	в хеш-таблице от числа n элементов в ней для заданных хеш-функций X и Y
	(см. распределение вариантов)
	 графики зависимости числа q коллизий от количества n элементов
	в хеш-таблице для заданных хеш-функций X и Y (см. распределение вариантов)

№ 1-20 	| Количество элементов	|					Хеш-функция X								|					Хеш-функция Y
		|  в словаре			| Время выполнения функции hashtab_lookup, с | Число коллизий	| Время выполнения функции hashtab_lookup, с | Число коллизий

*/


// ./a.out dictionaryns.dat 4 200000

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>

#include "bstree.h"
#include "hashtab.h"

#define clRed "\033[38;05;196m"
#define clBoldRed "\033[01;38;05;196m"
#define clNormal "\033[m"
#define clBoldBlue "\033[01;38;05;21m"
#define CLEAR "\033c"

int getrand(int min, int max)
{
	return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

//#define IFILE "dictionaryns.dat"
//#define WordsCount 1259840
#define WordsCount 1283313

char *Words[WordsCount];

void Read(char *IFILE)
{
	char word[100]= {' '};
	uint32_t CountWord = 0, CountSpace = 0;
	FILE* f;
	printf("\tОткрытие файла: %s\n", IFILE);
	// Попытка открыть файл
	if((f = fopen(IFILE, "r")) == NULL)
	{
		// Провалилась
		perror("fopen");
		exit(1);
	}
	printf("\tЧтение файла\n");
	register int inWord = 0;
	int c;
	int WLen = 0;
	double tN = 0;
	tN = wtime();
	while((c = getc(f)) != EOF)
	{
		if(isspace(c) || c == '\n')
		{
			inWord = 0;
			++CountSpace;
			if (WLen)
			{
				word[WLen] = '\0';
				Words[CountWord - 1] = (char*)malloc((WLen + 1) * sizeof(char));
				strcpy(Words[CountWord - 1], word);
			}
			WLen = 0;
		}
		else
		{
			word[WLen] = c;
			++WLen;
			if(inWord == 0)
			{
				inWord = 1;
				++CountWord;
			}
		}
	}
	tN = wtime() - tN;
	printf("\tФайл прочитан за %.8f сек. Содержит %d слов.\n", tN, CountWord);
//	printf("\tПрочитано слов: %d. Найдено пробелов/переносов: %d\n", CountWord, CountSpace-1);	
}

// Определение равномерности хеширования
unsigned int expe0(unsigned int Limit, int mode)
{
	if (WordsCount < Limit)
	{
		printf("\tСловарь не содержит такого числа слов.\n");
		exit(1);
	}
	int i;
	unsigned int CollisionCount = 0;
	int *CollisionMas = (int*)malloc(HASHTAB_SIZE * sizeof(int));
	for (i = 0; i < HASHTAB_SIZE; i++)
	{
		CollisionMas[i] = 0;
	}
	for (i = 0; i < Limit; i++)
	{
		switch (mode)
		{
			case 0:
				CollisionMas[FNV_Hash(Words[i])] += 1;
				break;
			case 1:
				CollisionMas[KP_Hash(Words[i])] += 1;
				break;
			case 2:
				CollisionMas[ADD_Hash(Words[i])] += 1;
				break;
			case 3:
				CollisionMas[XOR_Hash(Words[i])] += 1;
				break;
			case 4:
				CollisionMas[JENKINS_one_at_a_time_Hash(Words[i])] += 1;
				break;
		}
	}
	for (i = 0; i < HASHTAB_SIZE; i++)
	{
		if (CollisionMas[i] > 0)
		{
			CollisionMas[i]--;
			CollisionCount += CollisionMas[i];
		//	printf("%d\t%d\n", i, CollisionMas[i]);
		}
			
	}
	return CollisionCount;
}

void expe1(unsigned int Limit)
{
	if (WordsCount < Limit)
	{
		printf("\tСловарь не содержит такого числа слов.\n");
		exit(1);
	}
	int i, r, n;
	hashtab_init(hashtab);
	double tN = 0;
	
	// Создание хеш таблицы
	tN = wtime();
	printf("\tСоздание хеш таблицы из %d элементов: ", Limit);
  	for (i = 0; (i < WordsCount)&&(i < Limit) ; i++)
  	{
		hashtab_add(hashtab, Words[i], i, 0);
	}
	tN = wtime() - tN;
	printf("Создана за %.8f сек.\n", tN);
	
	double rd = 0;
	for (i = 0; i < 50000; i++)
	{
		r = getrand(0, Limit);
		tN = wtime();
		n = hashtab_lookup(hashtab, Words[r], 0)->value;
		rd += wtime() - tN;
	}
	printf("\t%sСреднее время выборки: %.8f сек.%s\n", clBoldRed, rd/50000, clNormal);



	// Создание бинарного дерева
	printf("\tСоздание бинарного дерева из %d элементов: ", Limit);
	struct bstree *tree ,*node;
	tree = bstree_create(Words[0],0);
	
	tN = wtime();
	for (i = 1; (i < WordsCount)&&(i < Limit) ; i++)
	{
		bstree_add(tree, Words[i], i);
	}

	tN = wtime() - tN;
	printf("Создано за %.8f сек.\n", tN);
	
	rd = 0;
	for (i = 0; i < 50000; i++)
	{
		r = getrand(0, Limit);
		tN = wtime();
		n = bstree_lookup(tree, Words[r])->value;
		rd += wtime() - tN;
	//	printf("%d %d\n", n, r);
	//	printf("%d, %s за %.8f сек.\n", n, rd, Words[r]);
	//	printf("%.8f\n",wtime() - tN);
	//	
	}
	printf("\t%sСреднее время выборки: %.8f сек.%s\n", clBoldRed, rd/50000, clNormal);
}

void expe4(unsigned int Limit)
{
	int i, r, n;
	double tN = 0;
	// Создание бинарного дерева
	printf("\tСоздание бинарного дерева из %d элементов: ", Limit);
	struct bstree *tree ,*node;
	tree = bstree_create(Words[0],0);
	
	tN = wtime();
	for (i = 1; (i < WordsCount)&&(i < Limit) ; i++)
	{
		bstree_add(tree, Words[i], i);
	}

	tN = wtime() - tN;
	printf("Создано за %.8f сек.\n", tN);

	tN = wtime();
	n = bstree_min(tree)->value;
	tN = wtime() - tN;
	printf("\t%sМинимум: %d \"%s\", за %.8f сек.%s\n", clBoldRed, bstree_min(tree)->value, bstree_min(tree)->key, tN, clNormal);

	tN = wtime();
	n = bstree_max(tree)->value;
	tN = wtime() - tN;
	printf("\t%sМаксимум: %d \"%s\", за %.8f сек.%s\n", clBoldRed, bstree_max(tree)->value, bstree_max(tree)->key, tN, clNormal);
}

void expe6(unsigned int Limit, int hashmode)
{
	if (WordsCount < Limit)
	{
		printf("\tСловарь не содержит такого числа слов.\n");
		exit(1);
	}
	int i, n, r;
	hashtab_init(hashtab);
	double tN = 0;
	
	// Создание хеш таблицы
	tN = wtime();
	printf("\tСоздание хеш таблицы из %d элементов: ", Limit);
  	for (i = 0; (i < WordsCount)&&(i < Limit) ; i++)
  	{
		hashtab_add(hashtab, Words[i], i, hashmode);
	}
	tN = wtime() - tN;
	printf("Создана за %.8f сек.\n", tN);
	
	double rd = 0;
	for (i = 0; i < 500000; i++)
	{
		r = getrand(0, Limit);
		tN = wtime();
		n = hashtab_lookup(hashtab, Words[r], hashmode)->value;
//	printf("%s %s\n", Words[n], Words[r]);
		rd += wtime() - tN;
	}
	printf("\t%sСреднее время выборки: %.8f сек.%s\n", clBoldRed, rd/500000, clNormal);
}

int main(int argc, char **argv)
{
	time_t t;
	srand((unsigned) time(&t));
	if (4 > argc)
		return 1;

	int mode = atoi(argv[2]);
	unsigned int Lim = atol(argv[3]);

	Read(argv[1]);
//	char *Words;
//	Words = (char*)malloc(sizeof(Words)*WordsCount);

//	expe1(WordsCount);

	switch (mode)
	{
		case 0:
			printf("К: %d для %d\n" ,expe0(Lim, atoi(argv[4])) , Lim);
			break;
		case 1:
			expe1(Lim);
			break;
		case 2:
			
			break;
		case 3:
			
			break;
		case 4:
			expe4(Lim);
			break;
		case 5:
			
			break;
		case 6:
			expe6(Lim, atoi(argv[4]));
			break;
	}



//	expe1(1250000);
//	expe4(1250000);
	
//	expe0(WordsCount, 0);
/*
Mode:
0:	FNV_Hash
1:	KP_Hash
2:	ADD_Hash
3:	XOR_Hash
4:	JENKINS_one_at_a_time_Hash
*/

	return 0;
}
