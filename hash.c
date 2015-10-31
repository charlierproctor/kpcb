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
	if (!h) {
		// malloc failed
		return NULL;
	}
	
	// initialize size, num_elements
	h->size = size;
	h->num_elements = 0;

	h->table = malloc(sizeof(Node) * h->size);
	if (!h->table) {
		// malloc failed
		free(h);
		return NULL;
	}

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
	if (strcpy(elem->key,key)) {
		// strcpy failed
		free(elem);
		free(elem->key);
		return false;
	}

	// attach the value to our struct
	elem->obj = value;

	// insert the element into the table
	size_t hash_val = hash(key) % h->size;
	elem->next = h->table[hash_val];
	h->table[hash_val] = elem;
	h->num_elements++;

	return true;
}

const void *hashGet(Hash *h, const char *key) {

	// iterate through the linked list at this index in the hash table.
	for (Node *elem = h->table[hash(key) % h->size]; elem; elem = elem->next) {
		// compare the key at this index to the desired key
		if (!strcmp(key,elem->key)) {
			// we found it!
			return elem->obj;
		}
	}
	// not in the table
	return NULL;
}

const void *hashDelete(Hash *h, const char *key) {
	
	// iterate through the linked list at this index in the hash table.
	// elem is the current element; previous is the previous elemetn
	for (Node *elem = h->table[hash(key) % h->size], *prev = NULL; 
		elem; 
		elem = (prev = elem)->next) {
		
		// compare the key at this index to the desired key
		if (!strcmp(key,elem->key)) {

			// update the pointers to remove this element from the table
			if (prev == NULL) {
				h->table[hash(key) % h->size] = elem->next;
			} else {
				prev->next = elem->next;
			}

			// one less element now :(
			h->num_elements--;

			// grab and return the object
			const void *res = elem->obj;
			free(elem->key);
			free(elem);
			return res;
		}
	}

	return NULL;
}

float hashLoad(Hash *h) {
	// just divide num_elements by size of table.
	return (float) h->num_elements / h->size;
}