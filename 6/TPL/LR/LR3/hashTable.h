#define HASHTABLESIZE 81
#define HT_PRIME_1 89
#define HT_PRIME_2 97

int hashFunction(char* s, int a, int m);
int getHash(char* s, int num_buckets, int attempt);

// Item in hash table
typedef struct {
	char* key;
	char* value;
} hashTableItem;

// Hashtable itself
typedef struct {
	int size;
	int itemCount;
	hashTableItem** items;
} hashTable;


hashTableItem* allocateNewItem (const char* key, const char* value);
hashTable* allocateNewTable();
void deleteItem(hashTableItem* myItem);
void deleteHashTable(hashTable* myTable);

//Api calls
void print_ht(hashTable* myHashtable);
void ht_insert(hashTable* myHashtable, char* key, char* value);
char* ht_search(hashTable* myHashtable, char* key);
