#include <stdio.h>
#include <stdlib.h>

struct node {
	char *str;
	void *obj;
	struct node *next;
};

struct hash {
	size_t size;			// size of the hash table
	size_t num_elements;  	// number of elements in the hash table

};

