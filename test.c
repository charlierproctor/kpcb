#include "hash.h"

#define USAGE "./test [dict] text"
#define DEFAULT "/usr/share/dict/words"
#define INITIAL_WORD_LENGTH 16

int main(int argc, char const *argv[]) {

	// bad usage
	if (argc < 2 || argc > 3) {
		fprintf(stderr, USAGE);
		exit(EXIT_FAILURE);
	} 

	// calculate dict / text strings
	const char *dictname, *textname;
	dictname = textname = NULL;

	if (argc == 2) {
		textname = argv[1];
		dictname = DEFAULT;
	} else {
		dictname = argv[1];
		textname = argv[2];
	}


	FILE *dict, *text;
	// open the dictionary and text files.
	if (!(dict = fopen(dictname,"r"))) {
		fprintf(stderr, "failed to open %s.", dictname);
		exit(EXIT_FAILURE);
	} else if (!(text = fopen(textname, "r"))) {
		fprintf(stderr, "failed to open %s.", textname);
		exit(EXIT_FAILURE);
	}

	int c; 
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

			// create an object
			bool *obj = malloc(sizeof(bool));
			*obj = true;

			// insert it into the table
			if (!hashSet(h,word,obj)) {
				fprintf(stderr, "failed to insert %s.", word);
				exit(EXIT_FAILURE);
			}

			// and create for the next word
			word = malloc(sizeof(char) * (size = INITIAL_WORD_LENGTH));
		} else {
			// set the character
			word[i++] = tolower(c);
		}
	}

	// free the word, as appropriate
	if (i) {
		free(word);
	}

	// malloc again
	word = malloc(sizeof(char) * (size = INITIAL_WORD_LENGTH));

	// read through the text file
	while ((c = fgetc(text)) != EOF) {
		// if the array is too small... make it bigger
		if (i >= size - 1) {
			word = realloc(word,(size *= 2));
		}
		if (c == '\n') {
			// null-terminate the word
			word[i] = '\0';
			i = 0;
			if (hashGet(h,word) == NULL) {
				printf("%s\n", word);
			}
		} else {
			// set the character
			word[i++] = tolower(c);
		}
	}

	// free the word
	free(word);
	

	return 0;
}