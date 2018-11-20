/* c1.c
Jim Plank
September, 1996 */

/* This program opens and closes the file "in1" in
a variety of ways.  Make sure you understand
this program, especially the return values of the
open calls. */

/* c1.c :: EDIT
Guillaume COQUARD
March, 2018 */

#include <stdio.h>
#include <stdlib.h>

#define DATA "./in1"

int main() {

	// Declaration of file descriptors
	FILE *f_1,*f_2;

	// File opening into first descriptor
	if ((f_1 = fopen(DATA,"r")) == NULL) {
		fprintf(stderr, "\nFailed : Unable to read this file : %s.\n", DATA);
		perror("Failed ");
		return (EXIT_FAILURE);
	}

	// File opening into second descriptor
	if ((f_2 = fopen(DATA,"r")) == NULL) {
		fprintf(stderr, "\nFailed : Unable to read this file : %s.\n", DATA);
		perror("Failed ");
		return (EXIT_FAILURE);
	}

	// Display descriptor ids
	printf("\nSuccess : The file in1 was opened twice : f's are %d and %d.\n",fileno(f_1),fileno(f_2));

	// File closing with first descriptor
	if (fclose(f_1) != 0) {
		fprintf(stderr, "\nFailed : Unable to close this file : %s.\n", DATA);
		perror("Failed ");
		return (EXIT_FAILURE);
	}
	// File closing with second descriptor
	if (fclose(f_2) != 0) {
		fprintf(stderr, "\nFailed : Unable to close this file : %s.\n", DATA);
		perror("Failed ");
		return (EXIT_FAILURE);
	}

	// Display it was correctly closed
	printf("\nSuccess : Both f's were closed.\n");

	// Re opening into second descriptor
	if ((f_2 = fopen(DATA,"r")) == NULL) {
		fprintf(stderr, "\nFailed : Unable to read this file : %s.\n", DATA);
		perror("Failed ");
		return (EXIT_FAILURE);
	}

	// Display if it succeed
	printf("\nSuccess : The file in1 was reopened into f_2 : %d.\n", fileno(f_2));

	// File reclosing with second descriptor
	if (fclose(f_2) != 0) {
		fprintf(stderr, "\nFailed : Unable to close this file : %s.\n", DATA);
		perror("Failed ");
		return (EXIT_FAILURE);
	}

	printf("\nSuccess : f_2 was closed.  Now, we will call fclose(f_2) again.\n");
	printf("This should cause an error.\n");

	// Test of reclosing in second descriptor - it won't work
	if (fclose(f_2) != 0) {
		fprintf(stderr, "\nFailed : Unable to close this file : %s.\n", DATA);
		perror("Failed ");
		return (EXIT_FAILURE);
	}

	return (0);

}
