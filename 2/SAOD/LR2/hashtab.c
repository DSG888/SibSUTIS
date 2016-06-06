#include "hashtab.h"

// Функции нахождения хешей
unsigned FNV_Hash(void *key)
{
	int len = strlen(key);
	unsigned char *p = key;
	unsigned h = 2166136261;
	int i;
	for (i = 0; i < len; i++)
	{
		h = (h * 16777619) ^ p[i];
	}
	return h % HASHTAB_SIZE;
}

unsigned int KP_Hash(char *key)
{
	unsigned int h = 0;
	char *p;
	for (p = key; *p != '\0'; p++)
	{
		h = h * HASHTAB_MUL + (unsigned int)*p;
	}
	return h % HASHTAB_SIZE;
}

unsigned int ADD_Hash(void *key)
{
	int len = strlen(key);
	unsigned char *p = key;
	unsigned h = 0;
	int i;

	for (i = 0; i < len; i++)
	{
		h += p[i];
	}
	return h % HASHTAB_SIZE;
}

unsigned int XOR_Hash(void *key) // Чоень плохая хеш функция
{
	int len = strlen(key);
	unsigned char *p = key;
	unsigned h = 0;
	int i;
	for (i = 0; i < len; i++)
	{
		h ^= p[i];
	}
	return h % HASHTAB_SIZE;
}

unsigned int JENKINS_one_at_a_time_Hash(char *key)
{
	int len = strlen(key);
	unsigned int hash, i;
	for(hash = i = 0; i < len; ++i)
	{
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash % HASHTAB_SIZE;
}
// Функции нахождения хешей

void hashtab_init(struct listnode **hashtab)//T Init = O(h)
{
	int i;
	for (i = 0; i < HASHTAB_SIZE; i++)
	{
		hashtab[i] = NULL;
	}
}
// Добавление элемента в хеш-таблицу
void hashtab_add(struct listnode **hashtab, char *key, int value, int mode)
{
	struct listnode *node;
	unsigned int index;
	switch (mode)
	{
		case 0:
			index = FNV_Hash(key);
			break;
		case 1:
			index = KP_Hash(key);
			break;
		case 2:
			index = ADD_Hash(key);
			break;
		case 3:
			index = XOR_Hash(key);
			break;
		case 4:
			index = JENKINS_one_at_a_time_Hash(key);
			break;
	}
	// Вставка в начало списка
	node = malloc(sizeof(*node));
	if (node == NULL)
	{
        	return;
	}
	node->key = key;
	node->value = value;
	node->next = hashtab[index];
	hashtab[index] = node;
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key, int mode)
{
	struct listnode *node;
	unsigned int index;
	switch (mode)
	{
		case 0:
			index = FNV_Hash(key);
			break;
		case 1:
			index = KP_Hash(key);
			break;
		case 2:
			index = ADD_Hash(key);
			break;
		case 3:
			index = XOR_Hash(key);
			break;
		case 4:
			index = JENKINS_one_at_a_time_Hash(key);
			break;
	}
	for (node = hashtab[index]; node != NULL; node = node->next)
	{
		if (strcmp(node->key, key) == 0)
			return node;
	}
	return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key, int mode)
{
	struct listnode *p, *prev = NULL;
	unsigned int index;
	// Выбор функции хэширования строки
	switch (mode)
	{
		case 0:
			index = FNV_Hash(key);
			break;
		case 1:
			index = KP_Hash(key);
			break;
		case 2:
			index = ADD_Hash(key);
			break;
		case 3:
			index = XOR_Hash(key);
			break;
		case 4:
			index = JENKINS_one_at_a_time_Hash(key);
			break;
	}
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
