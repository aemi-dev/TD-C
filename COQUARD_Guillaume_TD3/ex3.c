// © Guillaume COQUARD, March 2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// ASKED FUNCTIONS
// - add() function of exercise 3 of TD2
char *add(const char *dir, const char *name);
// - limit = fichiers trop gros
int limit(const char *path, int n);
// - list element in directory
int ls_dir(char *path);
// - list all regular file heavier than limit
int ls_heavy(char *path, int n);

// CONSTANTS NEEDED
#define SIZE 256

int main(int argc, char * argv[]) {
    if (argc>=1) {
        if (argc>2) {
            ls_heavy(argv[1],atoi(argv[2]));
        } else if (argc>1) {
            ls_heavy(argv[1],0);
        } else {
			ls_heavy("./",0);
		}
    }
    return 0;
}

char *add(const char *dir, const char *name) {

    char *ref = malloc((strlen(dir) + strlen(name) + strlen("/"))+1);
    strcpy(ref, dir);
    strcat(ref, "/");
    strcat(ref, name);
    return ref;

}

int limit(const char *path, int n) {
    struct stat file;
    if (stat(path,&file)!=0) {
        return (-1);
    }
    return file.st_size>n?0:1;
}

int ls_dir(char *path) {
    DIR *dir = NULL;
    struct dirent *file = NULL;

    if ((dir=opendir(path))==NULL) {
        perror("Directory cannot be opened because ");
        return (-1);
    }
    while ((file = readdir(dir)) != NULL) {
        printf("%s \n", file->d_name);
    }
    if (closedir(dir)==-1) {
        perror("Directory cannot be closed because ");
        return (-1);
    }
    return 0;
}

int ls_heavy(char *path, int n) {
    DIR *dir = NULL;
    struct dirent *file = NULL;
    if ((dir=opendir(path))==NULL) {
        perror("Directory cannot be opened because ");
        return (-1);
    }
    while ((file = readdir(dir)) != NULL) {
        if (limit(add(path,file->d_name),n)==0 && (file->d_type == DT_REG)) {
            printf("%s \n", file->d_name);
        }
    }
    if (closedir(dir)==-1) {
        perror("Directory cannot be closed because ");
        return (-1);
    }
    return 0;
}
