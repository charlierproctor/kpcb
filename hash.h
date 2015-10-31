#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
	char *key;					// the key of this element
	const void *obj;			// the arbitrary object reference
	struct node *next;			// next element the linked list
} Node;

typedef struct hash {
	Node **table;			// the hash table itself.
	size_t size;			// size of the hash table
	size_t num_elements;  	// number of elements in the hash table
} Hash;

Hash *hashCreate(size_t size);

bool hashSet(Hash *h, const char *key, const void *value);

const void *hashGet(Hash *h, const char *key);

const void *hashDelete(Hash *h, const char *key);

float *hashLoad(Hash *h);