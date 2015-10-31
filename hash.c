#include "hash.h"

Hash *hashCreate(size_t size) {
	// malloc for the table
	Hash *h = malloc(sizeof(Hash));
	
	// initialize size, num_elements
	h->size = size;
	h->num_elements = 0;

	h->table = malloc(sizeof(Node) * h->size);

	return h;
}
