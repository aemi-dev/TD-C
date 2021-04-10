/* write_ex.c :: EDIT
Guillaume COQUARD
March, 2018 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE_BUF 64

int main(int argc, char **argv){

	// It is also a pure converting of source file by using fwrite or fread

	char buf[SIZE_BUF];
	size_t nb_r;
	FILE *d_src, *d_targ;
	if (argc!=3) {
		return (1);
	}
	if ((d_src=fopen(argv[1],"r"))==NULL) {
		fprintf(stderr,"\nFailed : Unable to read this file : %s.\n",argv[1]);
		perror("Failed ");
		return (EXIT_FAILURE);
	} else {
		printf("Succeed : %s was opened with id %d.\n",argv[1],fileno(d_src));
	}
	if ((d_targ=fopen(argv[2],"w+"))==NULL) {
		fprintf(stderr,"\nFailed : Unable to read this file : %s.\n",argv[2]);
		perror("Failed ");
		return (EXIT_FAILURE);
	} else {
		printf("Succeed : %s was opened with id %d.\n",argv[2],fileno(d_targ));
	}
	do{
		nb_r = fread(buf, sizeof(char), SIZE_BUF, d_src);
		fwrite(buf, sizeof(char), nb_r, d_targ);
		if (nb_r==-1) {
			return (1);
		}
	}
	while (nb_r > 0);
	printf("Succeed : Copy is done.\n");
	if (fclose(d_src) != 0) {
		fprintf(stderr, "\nFailed : Unable to close this file : %s.\n", argv[1]);
		perror("Failed ");
		return (EXIT_FAILURE);
	}
	printf("Succeed : d_src was closed.\n");
	if (fclose(d_targ) != 0) {
		fprintf(stderr, "\nFailed : Unable to close this file : %s.\n", argv[2]);
		perror("Failed ");
		return (EXIT_FAILURE);
	}
	printf("Succeed : d_targ was closed.\n");

	return (0);

}
