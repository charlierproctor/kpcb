#include "hash.h"

#define INITIAL_STRING_LENGTH 32
#define USAGE "USAGE: ./play SIZE\n"
#define OPTIONS_FILE "options.txt"

// read an arbitrary length string from stdin.
char *readString(){
	// malloc for the initial string
	size_t size = INITIAL_STRING_LENGTH;
	char *str = malloc(sizeof(char) * size);
	size_t i = 0;

	int c;

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

// destroy one of our objects.
void destroy(void *obj) {
	// since we're dealing with malloc'd strings, we destroy with one free.
	free(obj);
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
	} else {
		printf("Successfully created a hash table of size %zu.\n",size);
		FILE *opt;
		if ((opt = fopen(OPTIONS_FILE,"r"))) {
			char c;
			while((c = fgetc(opt)) != EOF) {
				putchar(c);
			}
			fclose(opt);
		} else {
			fprintf(stderr, "failed to open %s\n", OPTIONS_FILE);
			exit(EXIT_FAILURE);
		}
	}

	// create some variables
	char *command, *key, *obj, *res;
	
	bool hasSet,hasGet,onOwn;
	hasSet = hasGet = onOwn = false;

	bool keepGoing = true;

	while(keepGoing) {
		// initialize the variables and print the prompt
		command = key = obj = res = NULL;

		// encourage the user to try out the different commands
		if (!hasSet) {
			printf("%% (type 'set') ");
		} else if (!hasGet) {
			printf("%% (type 'get') ");
		} else if (!onOwn) {
			onOwn = true;
			printf("You're on your own now... available commands: set, get, delete, load\n");
			printf("%% ");
		} else {
			printf("%% ");
		}

		// read the command
		command = readString();

		// process a set command
		if (!strcasecmp(command,"set")) {
			hasSet = true;
			printf("\tkey: ");
			key = readString();

			printf("\tvalue: ");
			obj = readString();

			printf("\tresult: ");
			printf(hashSet(h,key,obj) ? "SUCCESS\n" : "FAILURE\n");

		// process a get command
		} else if (!strcasecmp(command,"get")) {
			hasGet = true;
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

		// let the user exit
		} else if (!strcasecmp(command,"exit") || !strcasecmp(command,"quit")) {
			keepGoing = false;			

		// invalid command
		} else if (strlen(command) > 0) {
			printf("invalid command\n");
		} 

		// free the command and key, as necessary
		if (command) { free(command); }
		if (key) { free(key); }

	}

	hashDestroy(h,destroy);
	return EXIT_SUCCESS;
}