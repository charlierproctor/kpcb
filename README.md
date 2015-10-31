# KPCB Engineering Challenge Question

## Problem

> Using only primitive types, implement a fixed-size hash map that associates string keys with arbitrary data object references (you don't need to copy the object). Your data structure should be optimized for algorithmic runtime and memory usage. You should not import any external libraries, and may not use primitive hash map or dictionary 

## Solution

### Usage

- Run `make` to create the binary.
- Run `./hash SIZE`, where `SIZE` is the size of the hash table you wish to create.
- Now, you'll enter into a small bash-like environment to play with the hash table.

### Testing

In order to allow for easy / fun testing, I've put together a small bash-like environment to play with a hash table. The environment stores string values in the table.

After running `./hash SIZE`, you'll enter the environment.

The available commands:

- `set`: stores the given key/value pair in the hash table.
- `get`: return the value associated with the given key, or null if no value is set.
- `delete`: delete the value associated with the given key, returning the value on success or null if the key has no value.
- `load`: return a float value representing the load factor.
- `exit`: exits the environment

Note: You will separately be prompted for the command,key,value as appropriate. In other words, one command / key / value per line... `\n` is the delimiter.

### Design

- The hash table itself lies in the `hash.h`, `hash.c` files. `main.c` contains the code to run the environment.
- I'm using the `djb2` hash, found at [http://www.cse.yorku.ca/~oz/hash.html](http://www.cse.yorku.ca/~oz/hash.html)
- Everything is written in C, so the function take the following forms:

	```c
	Hash *hashCreate(size_t size);
	bool hashSet(Hash *h, const char *key, const void *value);
	const void *hashGet(Hash *h, const char *key);
	const void *hashDelete(Hash *h, const char *key);
	float hashLoad(Hash *h);
	```
	
- The data structures are defined as:

	```c
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
	```
	
- I wrote an optional `hashDestroy` function to free all the memory associated with the hash table. The second argument must be a function to destroy the arbitrary object passed in.

	```c
	void hashDestroy(Hash *h, void (*destroy)(void *obj));
	```
	
- The source code contains further design information, as laid out in the comments.