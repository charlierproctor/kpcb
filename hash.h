#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	char *str;					// the key of this element
	const void *obj;			// the arbitrary object reference
	struct node *next;			// next element the linked list
} Node;

typedef struct hash {
	Node **table;			// the hash table itself.
	size_t size;			// size of the hash table
	size_t num_elements;  	// number of elements in the hash table
} Hash;

Hash *hashCreate(size_t size);

bool hashSet(Hash *hash, const char *key, const void *value);

void *hashGet(Hash *hash, const char *key);

void *hashDelete(Hash *hash, const char *key);

float *hashLoad(Hash *hash);