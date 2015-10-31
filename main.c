#include "hash.h"

#define INITIAL_STRING_LENGTH 32
#define USAGE "USAGE: ./hash SIZE\n"

// read an arbitrary length string from stdin.
char *readString(){
	// malloc for the initial string
	size_t size = INITIAL_STRING_LENGTH;
	char *str = malloc(sizeof(char) * size);
	size_t i = 0;

	char c;

	// read chars until '\n'.
	while((c = getchar()) != '\n') {
		// user is trying to exit... let them
		if (c == EOF) {
			exit(EXIT_SUCCESS);
		}

		// if the array is too small... make it bigger
		if (i >= size - 2) {
			str = realloc(str,(size *= 2));
		}
		// set the character
		str[i++] = c;
	}
	// null-terminate the string
	str[i] = '\0';

	return str;
}

int main(int argc, char const *argv[]) {

	// default to a table of 1,000 elements.
	size_t size = 1000;

	if (argc > 1) {
		size = atoi(argv[1]);
		if (!size) {
			// couldn't convert argv[1] to a number
			fprintf(stderr, USAGE);
			exit(EXIT_FAILURE);
		}
	}

	// create a new hash table
	Hash *h = hashCreate(size);

	if (!h) {
		// failed to create hash table
		fprintf(stderr, "failed to create hash table\n");
		exit(EXIT_FAILURE);
	}

	// create some variables
	char *command, *key, *obj, *res;

	while(true) {
		// initialize the variables and print the prompt
		command = key = obj = res = NULL;
		printf("%% ");

		// read the command
		command = readString();

		// process a set command
		if (!strcasecmp(command,"set")) {
			printf("\tkey: ");
			key = readString();

			printf("\tvalue: ");
			obj = readString();

			printf("\tresult: ");
			printf(hashSet(h,key,obj) ? "SUCCESS\n" : "FAILURE\n");

		// process a get command
		} else if (!strcasecmp(command,"get")) {
			printf("\tkey: ");
			key = readString();
			if ((res = (char *) hashGet(h,key))){
				printf("\tresult: %s\n", res);
			} else {
				printf("\tresult: NULL\n");
			}

		// process a delete command
		} else if (!strcasecmp(command,"delete")) {
			printf("\tkey: ");
			key = readString();
			if ((res = (char *) hashDelete(h,key))){
				printf("\tresult: %s\n", res);
				free(res);
			} else {
				printf("\tresult: NULL\n");
			}

		// process a load command
		} else if (!strcasecmp(command,"load")) {
			printf("\tresult: %f\n", hashLoad(h));

		// invalid command
		} else if (strlen(command) > 0) {
			printf("invalid command\n");
		}

		// free the command and key, as necessary
		if (command) { free(command); }
		if (key) { free(key); }

	}

	return EXIT_SUCCESS;
}