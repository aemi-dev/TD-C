/* w1.c
Jim Plank
September, 1996 */

/* This program opens the file "out3" in the current
directory for writing, and writes the string "Hellow world!"
to it. */

/* w1.c :: EDIT
Guillaume COQUARD
March, 2018 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA "./out3"

int main() {

	// Declaration of file descriptor
	FILE *f;

	// Opening
	if ((f=fopen(DATA,"r+"))==NULL) {
        fprintf(stderr,"\nFailed : Unable to read this file : %s.\n",DATA);
        perror("Failed : tfile ");
        return (EXIT_FAILURE);
    } else {
		printf("\nSucceed : %s was opened with id %d\n",DATA,fileno(f));
	}

	// Pure converting of original file by using fwrite rather than write
	size_t sz = fwrite("Hello World!\n",sizeof(char),strlen("Hello World!\n"),f);
	printf("Computing : Command fwrite(\"Hello World!\\n\", sizeof(char), %lu, %d) was called.\n",strlen("Hello World!\n"),fileno(f));
	printf("Succeed : Command returned %zu.\n",sz);

	// Closing
    if (fclose(f) != 0) {
        fprintf(stderr,"\nFailed : Unable to close this file : %s.\n",DATA);
        perror("Failed ");
        return (EXIT_FAILURE);
    }
    printf("Succeed : f was closed.\n");

	return (0);

}
