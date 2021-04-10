//
//  main.c
//  Power Compiler
//
//  Created by Guillaume COQUARD on 08/03/2018.
//  Copyright © 2018 Guizilla. All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

#define SIZE 256
#define TITLE "./_ReadMe.txt"
#define TIME time(NULL)
#define HEAD "© Guillaume COQUARD - March, 2018"
#define NONEXT ""


int cmp(char *a,char *b);
void WR(char *a,FILE *b);
char *name(char *a);

int main(int argc, char * argv[]) {

	DIR *dir = NULL;
	struct dirent *file = NULL;
	FILE *readme;

	time_t a;
	time(&a);

	readme = fopen(TITLE,"w+");

	char *EXT_ORIGIN = malloc(2*sizeof(char)+1);
	strcpy(EXT_ORIGIN, ".c");

	char *EXT_TARGET = malloc(16*sizeof(char)+1);
	if (argv[1]!=NULL) {
		strcpy(EXT_TARGET,argv[1]);
	} else {
		strcpy(EXT_TARGET,"");
	}

	char *HEADER = malloc(SIZE*sizeof(char)+1);
	strcpy(HEADER,HEAD);
	strcat(HEADER,"\n\nAll .c files are compiled to ");
	if (strcmp(EXT_TARGET,NONEXT)!=0) {
		strcat(HEADER,EXT_TARGET);
	} else {
		strcat(HEADER,"without-extension");
	}
	strcat(HEADER," files.\n\nPairs of files are listed below :\n\n");

	WR(HEADER,readme);

	char *CMD = malloc(SIZE*sizeof(char)+1);
	strcpy(CMD,"gcc -Wall -pedantic -o ");

	char *path = malloc(SIZE*sizeof(char)+1);
	strcpy(path,".");

	if ((dir=opendir("."))==NULL) {
		perror("Directory cannot be opened because ");
		return (EXIT_FAILURE);
	}


	while ((file = readdir(dir)) != NULL) {

		strcat(path,"/");

		char *f_name = malloc(SIZE*sizeof(char)+1);
		size_t f_length = strlen(file->d_name);
		strcpy(f_name,file->d_name);

		char *dispairs = malloc(SIZE*sizeof(char)+1);
		strcpy(dispairs,"    - ");
		strcat(dispairs,f_name);
		strcat(dispairs,"\n");

		printf("# %s", f_name);

		if (f_length>2) {

			char *f_ext = malloc(2*sizeof(char)+1);
			f_ext[0] = f_name[f_length-2];
			f_ext[1] = f_name[f_length-1];

			char *f_next = malloc(SIZE*sizeof(char));
			strcpy(f_next,name(f_name));

			if (!cmp(f_ext,EXT_ORIGIN)) {
				char *cmd = malloc(SIZE*4*sizeof(char)+1);
				strcpy(cmd,CMD);
				char *nf_name = malloc(SIZE*sizeof(char)+1);
				strcpy(nf_name,f_next);
				if (!cmp(EXT_TARGET,"")) {
					strcat(nf_name,EXT_TARGET);
				}

				strcat(dispairs,"    - ");
				strcat(dispairs,nf_name);
				strcat(dispairs,"\n\n");

				char *i1 = malloc(SIZE*sizeof(char)+1);
				strcpy(i1,path);
				strcat(i1,nf_name);
				char *i2 = malloc(SIZE*sizeof(char)+1);
				strcpy(i2,path);
				strcat(i2,f_name);
				strcat(cmd,i1);
				strcat(cmd," ");
				strcat(cmd,i2);
				system(cmd);
				printf(" - COMPILED -> %s", nf_name);
				WR(dispairs,readme);
			}
		}
		printf("\n");
	}


	if (closedir(dir)==-1) {
		perror("Directory cannot be closed because ");
		return (EXIT_FAILURE);
	}

	WR("\n\nFiles were compiled on : ",readme);
	WR(ctime(&a),readme);

	fclose(readme);

	return (0);
}


void WR(char *a,FILE *f) {
	fwrite(a,sizeof(char),strlen(a),f);
}

char *name(char *a) {
	char *b = malloc(SIZE*sizeof(char));
	for (int i = 0; i < strlen(a)-2; i++) {
		b[i] = a[i];
	}
	return b;
}

int cmp(char *a, char *b) {
	int e = 0;
	if (strlen(a)!=strlen(b)) {
		return e;
	}
	for (int i = 0; (i<strlen(a)) && (e==0); i++) {
		a[i]==b[i]?e:e++;
	}
	return e;
}
