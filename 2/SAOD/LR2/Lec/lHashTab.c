#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHTAB_SIZE 71
#define HASHTAB_MUL 31

// Реализация хеш-таблицы
struct listnode
{
	char *key;
	int value;
	struct listnode *next;
};

struct listnode *hashtab[HASHTAB_SIZE];

// Хеш-функция
unsigned int hashtab_hash(char *key)//T Hash = O(|key|)
{
	unsigned int h = 0;
	char *p;
	for (p = key; *p != '\0'; p++)
	{
		h = h * HASHTAB_MUL + (unsigned int)*p;
	}
	return h % HASHTAB_SIZE;
}

// Инициализация хеш-таблицы
void hashtab_init(struct listnode **hashtab)//T Init = O(h)
{
	int i;
	for (i = 0; i < HASHTAB_SIZE; i++)
	{
		hashtab[i] = NULL;
	}
}

// Добавление элемента в хеш-таблицу
void hashtab_add(struct listnode **hashtab, char *key, int value)//T Add = T Hash + O(1) = O(1)
{
	struct listnode *node;
	int index = hashtab_hash(key);
	// Вставка в начало списка
	node = malloc(sizeof(*node));
	if (node != NULL)
	{
		node->key = key;
		node->value = value;
		node->next = hashtab[index];
		hashtab[index] = node;
	}
}

// Поиск элемента
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key)//T Lookup= T Hash + O(n) = O(n)
{
	int index;
	struct listnode *node;
	index = hashtab_hash(key);
	for (node = hashtab[index];	node != NULL; node = node->next)
	{
		if (strcmp(node->key, key) == 0)
			return node;
	}
	return NULL;
}

// Удаление элемента
void hashtab_delete(struct listnode **hashtab, char *key)//T Delete = T Hash + O(n) = O(n)
{
	int index;
	struct listnode *p, *prev = NULL;
	index = hashtab_hash(key);
	for (p = hashtab[index]; p != NULL; p = p->next)
	{
		if (strcmp(p->key, key) == 0)
		{
			if (prev == NULL)
				hashtab[index] = p->next;
			else
				prev->next = p->next;
			free(p);
			return;
		}
		prev = p;
	}
}

int main()
{
	struct listnode *node;
	hashtab_init(hashtab);
	hashtab_add(hashtab, "Tigr", 190);
	hashtab_add(hashtab, "Slon", 2300);
	hashtab_add(hashtab, "Volk", 60);
	node = hashtab_lookup(hashtab, "Slon");
	printf("Node: %s, %d\n",
	node->key, node->value);
	return 0;
}
