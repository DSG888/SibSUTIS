#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hashTable.h"

int hashFunction(char* s, int a, int m)
{
	long hash = 0;
	int i;
	int len_s = strlen(s);
	for (i = 0; i < len_s; i++)
	{
		hash += (long) (a * len_s - (i+1)) * s[i];
		hash = hash % m;
	}
	return (int)hash;
}

int getHash(char* s, int num_buckets, int attempt)
{
	int hash_a = hashFunction(s, HT_PRIME_1, num_buckets);
	int hash_b = hashFunction(s, HT_PRIME_2, num_buckets);
	return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

hashTableItem* allocateNewItem (const char* key, const char* value)
{
	hashTableItem* newItem = malloc(sizeof(hashTableItem));
	newItem->key = strdup(key);
	newItem->value = strdup(value);
	return newItem;
}

hashTable* allocateNewTable()
{
	hashTable* myTable = malloc(sizeof(hashTable));
	myTable->size = HASHTABLESIZE;
	myTable->itemCount = 0;
	myTable->items = calloc(HASHTABLESIZE, (sizeof(hashTableItem*)));;
	return myTable;
}

void deleteItem(hashTableItem* myItem)
{
	free(myItem->key);
	free(myItem->value);
	free(myItem);
	return;
}

void deleteHashTable(hashTable* myTable)
{
	int i;
	for(i = 0; i<HASHTABLESIZE; i++)
	{
		hashTableItem* item = myTable->items[i];
		if(item != NULL)
			deleteItem(item);
	}
	free(myTable->items);
	free(myTable);
	return;
}



void print_ht(hashTable* myHashtable)
{
	printf("\n===Printing hash table detailis===\n");
	printf("size is: %d\n", myHashtable->size);
	printf("itemCount is: %d\n", myHashtable->itemCount);
	int i;
	for (i=0;i<HASHTABLESIZE;i++)
	{
		hashTableItem* item = myHashtable->items[i];
		printf("item at index: %d has address: %p and points to: %p\n", i, (myHashtable->items) + i, myHashtable->items[i]);
		if (item != NULL)
			printf("item is: %s : %s\n\n", item->key, item->value);
	}
	printf("\n");
	return;
}


void ht_insert(hashTable* myHashtable, char* key, char* value)
{
	hashTableItem* newItem = allocateNewItem(key, value);
	int index = getHash(newItem->key, myHashtable->size, 0);
	hashTableItem* currentItem = myHashtable->items[index];
	int i = 1;
	while (currentItem != NULL)
	{
		if (strcmp(newItem->key, key) == 0)
		{
			printf("!!!!NO COLLISION\n");
			return;
		}
		printf("Collision at index: %d", index);
		index = getHash(newItem->key, myHashtable->size, i);
		currentItem = myHashtable->items[index];
		i++;
	}
	printf("ht_insert: inserting at index: %d for pair: %s: %s\n", index, key, value);
	myHashtable->items[index] = newItem;
	myHashtable->itemCount++;
	return;
}

char* ht_search(hashTable* myHashtable, char* key)
{
	int index = getHash(key, myHashtable->size, 0);
	printf("index is: %d\n", index);
	hashTableItem* item = myHashtable->items[index];
	int i = 1;
	while (myHashtable->items[index] != NULL)
	{
		if (strcmp(item->key, key) == 0)
			return item->value;
		index = getHash(key, myHashtable->size, i);
		item = myHashtable->items[index];
		i++;
	}
	return NULL;
}
