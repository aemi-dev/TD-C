/* r1.c
Jim Plank
September, 1996 */

/* This program shows some simple examples of using
the system call read() to read from a file. */

/* r1.c :: EDIT
Guillaume COQUARD
March, 2018 */

#include <stdio.h>
#include <stdlib.h>

#define DATA "./in1"

int main() {

	// Declaration of file descriptor
	FILE *f;

	// Prepare string
	char *c;
	c = (char*)calloc(100, sizeof(char));

	// Opening
	if ((f = fopen(DATA,"r")) == NULL) {
		fprintf(stderr, "\nFailed : Unable to read this file : %s.\n", DATA);
		perror("Failed ");
		return (EXIT_FAILURE);
	} else {
		printf("\nSucceed : %s was opened in f.\n", DATA);
	}

	// Perform reading and memorize value returned by action - size of string read
	size_t sz = fread(c, sizeof(char), 10, f);

	// Display what command was used and descriptor value
	printf("Succeed : We called : fread(c, sizeof(char), 10, %d).\n",fileno(f));

	// Display size of string read, in number of bytes
	printf("Succeed : Call returned that %zu bytes were read.\n", sz);

	// Affect empty character to c in index sz (size of string read in bytes)
	c[sz] = '\0';

	// Display bytes read which were stored in c
	printf("Those bytes are as follows: %s\n", c);

	// Repeat previous actions
	sz = fread(c, sizeof(char), 99, f);
	printf("Succeed : We called : fread(c, sizeof(char), 99, %d).\n",fileno(f));
	printf("Succeed : Call returned that %zu bytes were read.\n", sz);
	c[sz] = '\0';
	printf("Those bytes are as follows :\n%s", c);

	// Closing
	if (fclose(f) != 0) {
		fprintf(stderr, "\nFailed : Unable to close this file : %s.\n", DATA);
		perror("Failed ");
		return (EXIT_FAILURE);
	}
	printf("\nSucceed : f was closed.\n");
	
	return (0);

}
