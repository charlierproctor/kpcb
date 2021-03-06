# KPCB Engineering Challenge Question

## Problem

> Using only primitive types, implement a fixed-size hash map that associates string keys with arbitrary data object references (you don't need to copy the object). Your data structure should be optimized for algorithmic runtime and memory usage. You should not import any external libraries, and may not use primitive hash map or dictionary 

## Solution

### Build

- Run `make play` to create the `play` executable. 
- Run `make test` to create the `test` executable.
- `make clean` is there, in case you need it

### Play: A bash-like hash table environment

**Usage**: `./play SIZE`, where `SIZE` is the size of the hash table you wish to create

I've put together a small bash-like environment to play with a hash table. The environment stores string values in the table.

After running `./play SIZE`, you'll enter the environment.

The available commands:

- `set`: stores the given key/value pair in the hash table.
- `get`: return the value associated with the given key, or null if no value is set.
- `delete`: delete the value associated with the given key, returning the value on success or null if the key has no value.
- `load`: return a float value representing the load factor.
- `exit`: exits the environment

Note: You will separately be prompted for the command,key,value as appropriate. In other words, one command / key / value per line... `\n` is the delimiter.

### Test: A spell-checker

**Usage**: `./test [DICT]` where `DICT` is a dictionary of words to spell-check against. `DICT` defaults to `/usr/share/dict/words`.

Words are then read from `STDIN` and spell-checked. If they're mispelled, they're printed out.

1. The test script first creates a hash table and loads in the dictionary. 
2. The test script reads words from `STDIN` and checks to see if they are in the dictionary. If they are not, it prints them out (they're misspelled).

*./test performs a case-insensitive comparison.*

For example, if we wanted to find all the words the British mispell:
```
./test /usr/share/dict/american-english < /usr/share/dict/american-english
```

### Design

- The hash table itself lies in the `hash.h`, `hash.c` files. `main.c` contains the code to run the environment.
- I'm using the `djb2` hash, found at [http://www.cse.yorku.ca/~oz/hash.html](http://www.cse.yorku.ca/~oz/hash.html)
- To optimize for performance, I bring the last checked key to the front of the linked-list at the end of each `get`. Under the assumption that certain elements are accessed more frequently than others, this will decrease the search time at indices where there are collisions.
- Everything is written in C, so the functions take the following forms:

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
