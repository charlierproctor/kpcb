#include "hash.h"

#define USAGE "./test dict"
#define DEFAULT "/usr/share/dict/words"
#define INITIAL_WORD_LENGTH 16

// destroy one of our objects.
void destroy(void *obj) {
	// since we're dealing with malloc'd bools, we destroy with one free.
	free(obj);
}

int main(int argc, char const *argv[]) {

	// bad usage
	if (argc > 2) {
		fprintf(stderr, USAGE);
		exit(EXIT_FAILURE);
	} 

	// calculate dict string
	const char *dictname = (argc == 2 ? argv[1] : DEFAULT);

	FILE *dict;
	// open the dictionary file.
	if (!(dict = fopen(dictname,"r"))) {
		fprintf(stderr, "failed to open %s.", dictname);
		exit(EXIT_FAILURE);
	}

	int c; 
	// figure out how many words are in this dictionary
	size_t num_words = 0;
	while ((c = fgetc(dict)) != EOF) {
		num_words += (c == '\n');
	}
	fseek(dict,0,SEEK_SET);

	// create a hash table.
	Hash *h = hashCreate(num_words);
	if (!h) {
		fprintf(stderr, "failed to create hash table.");
		exit(EXIT_FAILURE);
	}

	// create the word buffer
	size_t size;
	char *word = malloc(sizeof(char) * (size = INITIAL_WORD_LENGTH));
	size_t i = 0; 

	// to track the loads
	size_t words = 0;
	float correct,actual;

	// read through the dictionary
	while ((c = fgetc(dict)) != EOF) {
		// if the array is too small... make it bigger
		if (i >= size - 1) {
			word = realloc(word,(size *= 2));
		}
		if (c == '\n') {
			// null-terminate the word, reset i.
			word[i] = '\0';
			i = 0;
			words++;

			// create an object
			bool *obj = malloc(sizeof(bool));
			*obj = true;

			// insert it into the table
			if (!hashSet(h,word,obj)) {
				fprintf(stderr, "failed to insert %s.", word);
				exit(EXIT_FAILURE);
			}

			// check the load
			if ((actual = hashLoad(h)) != (correct = (float) words / num_words)) {
				fprintf(stderr, "load: %f != %f\n",actual,correct);
				exit(EXIT_FAILURE);
			}
		} else {
			// set the character
			word[i++] = tolower(c);
		}
	}

	// read through words from stdin
	while ((c = getchar()) != EOF) {
		// if the array is too small... make it bigger
		if (i >= size - 1) {
			word = realloc(word,(size *= 2));
		}
		if (c == '\n') {
			// null-terminate the word
			word[i] = '\0';
			i = 0;
			if (hashGet(h,word) == NULL) {
				printf("mispelled: %s\n", word);
			}
		} else {
			// set the character
			word[i++] = tolower(c);
		}
	}

	// free the word
	free(word);
	
	hashDestroy(h,destroy);

	return 0;
}