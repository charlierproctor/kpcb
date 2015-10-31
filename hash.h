#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

// node in the hash table.
typedef struct node {
	char *key;					// the key of this element
	const void *obj;			// the arbitrary object reference
	struct node *next;			// next element the linked list
} Node;

// the hash table itself
typedef struct hash {
	Node **table;			// the hash table itself.
	size_t size;			// size of the hash table
	size_t num_elements;  	// number of elements in the hash table
} Hash;

/**
 * @brief      create a new hash table
 *
 * @param[in]  size  size of the hash table to create
 *
 * @return     pointer to the new hash table
 */
Hash *hashCreate(size_t size);

/**
 * @brief       stores the given key/value pair in the hash map. 
 *
 * @param      h      the hash table into which we will insert
 * @param[in]  key    key under which to insert
 * @param[in]  value  value to insert
 *
 * @return     whether the element was successfully inserted
 */
bool hashSet(Hash *h, const char *key, const void *value);

/**
 * @brief      return the value associated with the given key, 
 *             or null if no value is set.
 *
 * @param      h     the hash table
 * @param[in]  key   key to search under
 *
 * @return     value associated with key, or NULL if key DNE
 */
const void *hashGet(Hash *h, const char *key);

/**
 * @brief      delete the value associated with the given key, returning 
 *             the value on success or null if the key has no value.
 *
 * @param      h     the hash table
 * @param[in]  key   key to remove
 *
 * @return     value if the element exists and was deleted, NULL otherwise.
 */
const void *hashDelete(Hash *h, const char *key);

/**
 * @brief      return a float value representing the load factor
 *
 * @param      h     the hash table
 *
 * @return     the load factor
 */
float hashLoad(Hash *h);

/**
 * @brief      destroy the hash table, free'ing all memory
 *
 * @param      h        the hash table to destroy
 * @param[in]  destroy  function to destroy an element
 */
void hashDestroy(Hash *h, void (*destroy)(void *obj));