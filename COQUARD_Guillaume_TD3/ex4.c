// © Guillaume COQUARD, March 2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// ASKED FUNCTIONS
// - add() : function of exercise 3 of TD2
char *add(const char *dir, const char *name);
// - list directory in passed directory
int ls_all(char *path);

// CONSTANTS NEEDED
#define SIZE 256

int main(int argc, char * argv[]) {
	if (argc!=2) {
	    ls_all("./");
	} else {
		ls_all(argv[1]);
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

int ls_all(char *path) {
    DIR *dir = NULL;
    struct dirent *file = NULL;

    if ((dir=opendir(path))==NULL) {
        perror("Directory cannot be opened because ");
        return (-1);
    }

    while ((file = readdir(dir)) != NULL) {

        if (file->d_type == DT_DIR) {
            printf("%s \n", file->d_name);
        } else if (file->d_type == DT_LNK) { // display link
			printf("[link] %s \n", file->d_name);
		}

    }

    if (closedir(dir)==-1) {
        perror("Directory cannot be closed because ");
        return (-1);
    }

    return 0;
}
