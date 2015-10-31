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

	// read chars until ' ', '\n' or EOF.
	while((c = getchar()) != EOF && (c != ' ') && (c != '\n')) {
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

	char *command, *key, *obj, *res;
	command = key = obj = res = NULL;

	while(true) {
		printf("%% ");

		// read the command
		command = readString();

		if (!strcasecmp(command,"set")) {
			key = readString();
			obj = readString();
			printf("hashSet: ");
			printf(hashSet(h,key,obj) ? "SUCCESS\n" : "FAILURE\n");
		} else if (!strcasecmp(command,"get")) {
			key = readString();
			if ((res = (char *) hashGet(h,key))){
				printf("hashGet: %s\n", res);
			} else {
				printf("hashGet: NULL\n");
			}
		} else if (!strcasecmp(command,"delete")) {
			key = readString();
			if ((res = (char *) hashDelete(h,key))){
				printf("hashDelete: %s\n", res);
			} else {
				printf("hashDelete: NULL\n");
			}
		} else if (!strcasecmp(command,"load")) {
			printf("hashLoad: %f\n", hashLoad(h));
		} else {
			printf("invalid command\n");
		}

	}

	return EXIT_SUCCESS;
}