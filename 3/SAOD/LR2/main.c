/*
- В файле trie.c реализовать функции для работы с префиксным деревом
- Ключ – нуль-терминальная последовательность символов в кодировке ASCII (char *)
- Cписок дочерних узлов хранить в связном списке {child, sibling} (см. лекцию)
struct trie *trie_create()
char *trie_lookup(struct trie *root, char *key)
struct trie *trie_insert(struct trie *root, char *key, char *value)
struct trie *trie_delete(struct trie *root, char *key)
void trie_print(struct trie *root, int level)
- Объяснить алгоритмы выполнение операций префиксного дерева и оценить их вычислительную сложность
- Как модифицировать код для реализации упорядоченного словаря (ordered map)?
- Сравнить вычислительную сложность операций префиксного дерева со сбалансированными деревьями поиска и хеш-таблицами
*/

#include <stdio.h>
#include <stdint.h>
#include "trie.h"

//#define WordsCount 1283313
#define WordsCount 80368
char *Words[WordsCount];
char *UserWords[1000];
char *UserVol[1000];

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
	printf("\tФайл прочитан. Содержит %d слов.\n", CountWord);
}

/* itoa:  конвертируем n в символы в s */
void mitoa(int n, char s[])
{
	/* reverse:  переворачиваем строку s на месте */
	void reverse(char s[])
	{
		int i, j;
		char c; 
		for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
			c = s[i];
			s[i] = s[j];
			s[j] = c;
		}
	}
	int i, sign; 
	if ((sign = n) < 0)  /* записываем знак */
		n = -n;          /* делаем n положительным числом */
	i = 0;
	do {       /* генерируем цифры в обратном порядке */
		s[i++] = n % 10 + '0';   /* берем следующую цифру */
	} while ((n /= 10) > 0);     /* удаляем */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int menu()
{
	int req;
	printf(" 1 Добавить слово\n");
	printf(" 2 Найти слово\n");
	printf(" 3 Удалить слово\n");
	printf(" 4 Дополнить слово\n");
	printf(" 5 Вывод всего дерева (большой вывод)\n");
	printf(" 0 Выход\n? ");
	scanf("%d", &req);
	return req;
}

int main(int argc, char **argv)
{
	// Загрузка словаря
	Read("dictionary.txt");
	struct trie *root;
	int i, req = -1, zz = 0;
	root = trie_insert(NULL, Words[0], "0");
//root = trie_insert(NULL, "0", "0");
	// Построение структуры
	for (i = 1; i < WordsCount; i++)
	{
		char str[10];
		mitoa(i, str);
		root = trie_insert(root, Words[i], str);
	}
	// Взаимодействие с пользователем
	
	while (req)
	{
		printf("\n\n\n\n===============================================\n");
		req = menu();
		switch(req)
		{
			char buf[25];
			case 1:
				UserWords[zz] = (char*)malloc((100 + 1) * sizeof(char));
				UserVol[zz] = (char*)malloc((100 + 1) * sizeof(char));
				printf(" Введите строку: ");
				scanf("%s", UserWords[zz]);
				printf(" Введите значение: ");
				scanf("%s", UserVol[zz]);
			
				root = trie_insert(root, UserWords[zz], UserVol[zz]);
				req = -1;
				zz++;
				break;
			case 2:
				printf(" Введите искомую строку: ");
				scanf("%s", buf);
				printf("Искомая строка содержит ключ: %s\n", trie_lookup(root, buf));
				req = -1;
				break;
			case 3:
				printf(" Введите удаляемое слово: ");
				scanf("%s", buf);
				root = trie_delete(root, buf);
				req = -1;
				break;
			case 4:
				printf(" Введите дополняемое слово: ");
				scanf("%s", buf);
				trie_find(root, buf);
				req = -1;
				break;
			case 5:
				trie_print(root, 0);
				break;
		}
	}
	return 0;
}
