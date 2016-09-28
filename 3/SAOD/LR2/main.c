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
#include "trie.h"

int main(int argc, char **argv)
{
	struct trie *root;
	root = trie_insert(NULL, "bars", "60");
	root = trie_insert(root, "baribal", "100");
	root = trie_insert(root, "kit", "3000");
	root = trie_insert(root, "lev", "500");
	root = trie_insert(root, "bars", "70");
	trie_print(root, 0);
	printf("Lookup 'bars': %s\n",
	trie_lookup(root, "bars"));
	root = trie_delete(root, "bars");
	trie_print(root, 0);
	return 0;
}
