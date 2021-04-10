#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

#define SIZE 256

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

int main(int argc, char * argv[]) {

	DIR *dir = NULL;
	struct dirent *file = NULL;

    char *EXT_ORIGIN = malloc(2*sizeof(char)+1);
    strcpy(EXT_ORIGIN, ".c");

    char *EXT_TARGET = malloc(16*sizeof(char)+1);
    if (argv[1]!=NULL) {
        strcpy(EXT_TARGET,argv[1]);
    } else {
        strcpy(EXT_TARGET,".out");
    }

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

        printf("# %s", f_name);

        if (f_length>2) {

            char *f_ext = malloc(2*sizeof(char)+1);
            f_ext[0] = f_name[f_length-2];
            f_ext[1] = f_name[f_length-1];

            if (!cmp(f_ext,EXT_ORIGIN)) {
                char *cmd = malloc(SIZE*4*sizeof(char)+1);
                strcpy(cmd,CMD);
                char *nf_name = malloc(SIZE*sizeof(char)+1);
                strcpy(nf_name,file->d_name);
                for (int i = 0; i < strlen(EXT_TARGET); i++) {
                    nf_name[f_length-2+i] = EXT_TARGET[i];
                }

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
            }
        }
        printf("\n");
    }


    if (closedir(dir)==-1) {
        perror("Directory cannot be closed because ");
        return (EXIT_FAILURE);
    }

    return (0);
}
