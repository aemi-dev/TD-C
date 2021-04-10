/* r1.c :: EDIT
Guillaume COQUARD
March, 2018 */

#include <stdio.h>
#include <stdlib.h>

#define DATA "./tfile"

int main(void){

	// Declaration of an array of pointer-descriptor of file
    FILE *f[2];

    char buf1[12] = "just a test";
    char buf2[12];

    if ((f[0]=fopen(DATA,"rw"))==NULL) {
        fprintf(stderr, "\nFailed : Unable to read this file : %s.\n", DATA);
        perror("Failed : tfile ");
        return (EXIT_FAILURE);
    }
    printf("Succeed : %s opened with id %d.\n", DATA,fileno(f[0]));
    if ((f[1]=fopen(DATA,"rw"))==NULL) {
        fprintf(stderr, "\nFailed : Unable to read this file : %s.\n", DATA);
        perror("Failed : tfile ");
        return (EXIT_FAILURE);
    }
    printf("Succeed : %s opened with id %d.\n", DATA,fileno(f[1]));

	// Writing on tfile with f[0] from buf1
    printf("\nComputing : Writing \"%s\" on file with id %d.\n", buf1,fileno(f[0]));
    fwrite(buf1, sizeof(char), sizeof buf1, f[0]);
    printf("Computing : Reading file with id %d.\n",fileno(f[1]));
    printf("Computing : Writing on standard output.\n");
	// Write on stdout while reading tfile with f[1] to buf2
	fwrite(buf2, sizeof(char), fread(buf2, sizeof(char), sizeof buf1, f[1]), stdout);
    printf("\n");

	// Closing
    if (fclose(f[0]) != 0) {
        fprintf(stderr, "\nFailed : Unable to close this file : %s.\n", DATA);
        perror("Failed ");
        return (EXIT_FAILURE);
    }
    printf("\nSucceed : f[0] was closed.\n");
    if (fclose(f[1]) != 0) {
        fprintf(stderr, "\nFailed : Unable to close this file : %s.\n", DATA);
        perror("Failed ");
        return (EXIT_FAILURE);
    }
    printf("Succeed : f[1] was closed.\n");

    return (0);
	
}
