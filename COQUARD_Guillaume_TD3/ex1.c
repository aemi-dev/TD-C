// © Guillaume COQUARD, March 2018

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define __RIGHTS__ 0777 // rights : rwxrwxrwx

int mktddir(const char *prefix, char *suffix);

int main(int argc, char **argv) {
	mktddir(argv[1],argv[2]);
	return 0;
}

int mktddir(const char *prefix, char *suffix) {

	char *root = malloc(128*sizeof(char)+1), *el = malloc(128*sizeof(char)+1);
	strcpy(root,"./");
	strcat(root,prefix);

	if ( !mkdir(root,__RIGHTS__) ) {
		perror("Failed ");
		return(-1);
	}

	chdir(root);

	int i;
	for (i=1;i<=atoi(suffix);i++) {
		char *id = malloc(8*sizeof(char)+1);
		strcpy(el,"./td");
		snprintf(id,8*sizeof(char),"%d",i);
		strcat(el,id);
		mkdir(el,__RIGHTS__);
	}

	return 0;
}
