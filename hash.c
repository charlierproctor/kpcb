#include "hash.h"

// djb2 hash function, taken from http://www.cse.yorku.ca/~oz/hash.html
size_t hash(const char *str)
{
    size_t hash = 5381;
    int c;
    while ((c = (unsigned) *str++)) {
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

bool hashSet(Hash *h, const char *key, const void *value) {

	// create a new node
	Node *elem = malloc(sizeof(Node));
	if (!elem) {
		// malloc failed
		return false;
	}
	
	// malloc for the key
	elem->key = malloc(sizeof(char) * (strlen(key) + 1));
	if (!elem->key) {
		// malloc failed
		free(elem);
		return false;
	}
	// copy in the string
	strcpy(elem->key,key);

	// attach the value to our struct
	elem->obj = value;

	// insert the element into the table
	size_t hash_val = hash(key) % h->size;
	elem->next = h->table[hash_val];
	h->table[hash_val] = elem;

	return true;
}
