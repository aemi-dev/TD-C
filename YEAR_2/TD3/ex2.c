// © Guillaume COQUARD, March 2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define SIZE 256

int main(int argc, char * argv[]) {

	DIR *dir = NULL;
	struct dirent *file = NULL;
	char *path = malloc(SIZE*sizeof(char)+1);

	if (argc<2) {
		return(-1);
	}

	strcat(path,argv[1]);

	if ((dir=opendir(path))==NULL) {
		perror("Directory cannot be opened because ");
		return (-1);
	}

	while ((file = readdir(dir)) != NULL) {
		printf("# %s \n", file->d_name);
	}

	if (closedir(dir)==-1) {
		perror("Directory cannot be closed because ");
		return (-1);
	}

	return (0);
}
