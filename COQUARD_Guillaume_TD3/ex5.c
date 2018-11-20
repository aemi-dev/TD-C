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
// - return a string represents parent directory of open directory
char *get_parent(char *path);

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

char *get_parent(char *path) {
	// get_parent return element between "/" before current element
    char *a = malloc(strlen(path)*sizeof(char)+1);
	strcpy(a,"");
    int i, j, k = 0;
    for (i = (int)strlen(path)-1; i>=0 && k==0; i--) {
        if (path[i]=='/' && i<strlen(path)) {
            for (j = i+1; j<strlen(path); j++) {
                if (path[j]!='/') {
                    a[j-i-1] = path[j];
                }
            }
			++k;
        }
    }
    return a[0]=='\0'?".":a;
}

int ls_all(char *path) {
    DIR *dir = NULL;
    struct dirent *file = NULL;

	if ((dir=opendir(path))==NULL) {
        perror("Directory cannot be opened because ");
        return (-1);
    }

	// First loop to display matching element
	while ((file = readdir(dir)) != NULL) {

		char *name = malloc(SIZE*sizeof(char)+1);
        strcpy(name,file->d_name);

		// Condition to not display "." & ".." element
		char v2[1] = ".";
		if (name[0]!=v2[0] || ((strlen(name)==2)&&(name[0]==v2[0])&&(name[1]!=v2[0])) || (strlen(name)>2)) {
            if (file->d_type == DT_DIR) { // Check if file is a directory
                printf("%s -> %s \n", get_parent(path), name);
            }
        }

	}

	if (closedir(dir)==-1) {
        perror("Directory cannot be closed because ");
        return (-1);
    }

	// Second loop to open matching element
	dir=opendir(path);
    while ((file = readdir(dir)) != NULL) {

		char *name = malloc(SIZE*sizeof(char)+1);
        strcpy(name,file->d_name);

		// Condition to not open "." & ".." element
		char v2[1] = ".";
		if (name[0]!=v2[0] || ((strlen(name)==2)&&(name[0]==v2[0])&&(name[1]!=v2[0])) || (strlen(name)>2)) {
            if (file->d_type == DT_DIR) {
                ls_all(add(path,name));
            }
        }

	}
    closedir(dir);
    return 0;
}
