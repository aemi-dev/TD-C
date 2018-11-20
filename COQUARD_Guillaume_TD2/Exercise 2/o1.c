/* This program opens the file "in1" in the current
directory, and prints out the return value of
the open() system call.  If "in1" exists, open()
will return a non-negative integer (three).  If
"in1" does not exist, then it will return -1. */

/* o1.c :: EDIT
Guillaume COQUARD
March, 2018 */

#include <stdio.h>
#include <stdlib.h>

#define DATA "./in1"

int main() {

	// Declaration of file descriptors
	FILE *f;

	// Opening file into f descriptor
	if ((f = fopen(DATA,"r")) == NULL) {
		fprintf(stderr, "\nFailed : Unable to read this file : %s.\n", DATA);
		perror("Failed ");
		return (EXIT_FAILURE);
	} else {
		printf("\nSucceed : %s was opened with id %d.\n",DATA,fileno(f));
	}

	// Closing file with f
	if (fclose(f) != 0) {
		fprintf(stderr, "\nFailed : Unable to close this file : %s.\n", DATA);
		perror("Failed ");
		return (EXIT_FAILURE);
	}
	printf("\nSucceed : f was closed.\n");

	return (0);

}
