/* o2.c
Jim Plank
September, 1996 */

/* This program attempts to opens the file "out1"
for writing in the current directory.  Note that
this fails because "out1" does not exist already.
See o3.c for an example of a opening "out1"
properly. */

/* o2.c :: EDIT
Guillaume COQUARD
March, 2018 */

#include <stdio.h>
#include <stdlib.h>

#define DATA "./out1"

int main() {

	// Declaration of file descriptors
	FILE *f;

	// Opening file into f descriptor
	if ((f=fopen(DATA,"w+"))==NULL) {
		fprintf(stderr, "\nFailed : Unable to read this file : %s.\n", DATA);
		perror("Failed : out1 ");
		return (EXIT_FAILURE);
	}
	else {
		printf("\nSucceed : %s was opened with id %d.\n", DATA,fileno(f));
		// Display descriptor value
		printf("Succeed : %d is ready to be read.\n",fileno(f));
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
