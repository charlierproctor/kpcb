#include "hash.h"

// djb2 hash function, taken from http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

Hash *hashCreate(size_t size) {
	// malloc for the table
	Hash *h = malloc(sizeof(Hash));
	
	// initialize size, num_elements
	h->size = size;
	h->num_elements = 0;

	h->table = malloc(sizeof(Node) * h->size);

	return h;
}

bool hashSet(Hash *h, const char *key, const void *value);
