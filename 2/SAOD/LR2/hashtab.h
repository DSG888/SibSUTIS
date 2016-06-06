#ifndef myHashTab
#define myHashTab

#include <string.h>
#include <stdlib.h>

#define HASHTAB_MUL 31
#define HASHTAB_SIZE 40960

unsigned FNV_Hash(void *key);
unsigned int KP_Hash(char *key);
unsigned int ADD_Hash(void *key);
unsigned int XOR_Hash(void *key);
unsigned int JENKINS_one_at_a_time_Hash(char *key);


struct listnode *hashtab[HASHTAB_SIZE];

struct listnode
{
	char *key;
	int value;
	struct listnode *next;
};

void hashtab_init(struct listnode **hashtab);

void hashtab_add(struct listnode **hashtab, char *key, int value, int mode);
/*
Mode:
0:	FNV_Hash
1:	KP_Hash
2:	ADD_Hash
3:	XOR_Hash
4:	JENKINS_one_at_a_time_Hash
*/

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key, int mode);

void hashtab_delete(struct listnode **hashtab, char *key, int mode);

#endif
