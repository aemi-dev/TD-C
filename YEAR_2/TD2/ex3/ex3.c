//
//
//  Created by Guillaume COQUARD on 09/03/2018.
//  Copyright © 2018 Guizilla. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>



// ASKED FUNCTIONS
// -- verifie()
int check(struct stat *buf, ino_t ino, size_t max, size_t min, mode_t m);
// -- ajoute()
char *add(const char *dir, const char *name);
// -- trouve() -- finder action
int find(const char *dir, int depth, ino_t ino, size_t max, size_t min, mode_t m);



// PERSONAL FUNTIONS
// -- display informations about passed arguments or default values to finder
void info(char *dir, int depth, int ino, int max, int min, char *mode);
// -- translate rights arg (string) to rights value (integer)
int tav(char *a);
// -- translate rights from stat to rights value (integer)
int trv(struct stat *buf);
// -- translate rights value to rights string
char *tvr(struct stat *buf);



// CONSTANTS NEEDED
#define SIZE 512 // easy method to use longer path
int DTH; // depth global value



int main(int argc, char * argv[]) {

	printf("\nPassed Values : \n");

	int r = 0; // Main Finder's Returned Value Initialization

	if (argc!=11) { // Almax argument-free use

		DTH = 3; // Default depth Value

		info(".",DTH,10,1000000000,0,"---");

		printf("<-- Every repertories met on filefinding will be displayed. -->\n");

		printf("\n . Analysis : \n\n");
		// Pass default values to Finder's Function
		r = find(".",DTH,10,1000000000,0,tav("---"));

    } else {

        DTH = atoi(argv[2]);

		info(argv[1],DTH,atoi(argv[4]),atoi(argv[6]),atoi(argv[8]),argv[10]);

		printf("<-- Every repertories met on filefinding will be displayed. -->\n");

		printf("\n%s Analysis : \n\n",argv[1]);
		// Pass args to Finder's Function
        r = find(argv[1],DTH,atoi(argv[4]),atoi(argv[6]),atoi(argv[8]),tav(argv[10]));

	}

    printf("\n<-- No more files match your criterias. -->\n\n");

    return r;

}



void info(char *dir, int depth, int ino, int max, int min, char *mode) {
	printf("|   Path ........ : %s\n|   Depth ....... : %d\n|   Node Number . : %d\n|   Max. Size ... : %d\n|   Min. Size ... : %d\n|   Rights ...... : %s\n",dir,depth,ino,max,min,mode);
}



int tav(char *a) {

    int rwx = 0; // Value to return

    int i;
    for (i = 0; i<strlen(a)+1; i++) {

		// Values are based on returned value of : XX->st_mode & S_I(R||W||X)USR
		switch (a[i]) {

            case 'r' :
                rwx += 256;
                break;
            case 'w' :
                rwx += 128;
                break;
            case 'x' :
                rwx += 64;
                break;
            case '-' :
                rwx += 0;
                break;
            default:
                break;

        }

    }

    return rwx;

}



int trv(struct stat *buf) {

    int rwx = 0;

    rwx += buf->st_mode & S_IRUSR; // Read-access ? 256 : 0
    rwx += buf->st_mode & S_IWUSR; // Write-access ? 128 : 0
    rwx += buf->st_mode & S_IXUSR; // Exec.-access ? 64 : 0

    return rwx;

}



char *tvr(struct stat *buf) {

    char *a = malloc(3*sizeof(char));

    switch (trv(buf)) {
        case 256 :
            strcpy(a,"r--");
            break;
        case 128 :
            strcpy(a,"-w-");
            break;
        case 64 :
            strcpy(a,"--x");
            break;
        case 0 :
            strcpy(a,"---");
            break;
        case 384 :
            strcpy(a,"rw-");
            break;
        case 320 :
            strcpy(a,"r-x");
            break;
        case 192 :
            strcpy(a,"-wx");
            break;
        case 448 :
            strcpy(a,"rwx");
            break;
        default:
            break;
	}

	return a;
}



int check(struct stat *buf, ino_t ino, size_t max, size_t min, mode_t m) {

    int i = 0;

    if (buf->st_ino == ino) { // Is buf's i-node correct ?
        i++;
    }

    if (buf->st_size < max) { // Is buf's size correct ?
        i++;
    }

    if (buf->st_size > min) { // Is buf's size correct ?
        i++;
    }

    if (trv(buf) >= m) { // Are buf's rights correct ?
        i++;
    }

    i = (i==4?1:-1);

    return i;

}



char *add(const char *dir, const char *name) {

	char *ref = malloc((strlen(dir) + strlen(name) + strlen("/"))+1);
    strcpy(ref, dir);
    strcat(ref, "/");
    strcat(ref, name);
    return ref;

}


int find(const char *dir, int depth, ino_t ino, size_t max, size_t min, mode_t m) {

    int f = 0; // Value to return

    DIR *directory = NULL;
    struct dirent *element = NULL;
    struct stat st_element;

	// Check if element at path is an openable directory
    if ((directory=opendir(dir))==NULL) {

        fprintf(stderr, "Failed : Unable to open this directory : %s\n", dir);
        perror("Failed : Unable to open this directory ");

        return ++f; // Return 1 if it is not

    }

	// Define path to dir as variable -- simplifies use
    char *dry = malloc(strlen(dir)+1);
    strcpy(dry,dir);

	// While element is readable
    while ((element = readdir(directory)) != NULL) {

		// Define element name as variable -- simplifies use
		char *el_name = malloc(SIZE+1);
        strcpy(el_name, element->d_name);

		// Avoid . and .. computing
        char v2[1] = ".";
		if (el_name[0]!=v2[0] || ((strlen(el_name)==2)&&(el_name[0]==v2[0])&&(el_name[1]!=v2[0])) || (strlen(el_name)>2)) {

			// Define path to element as variable (path_to_dir/path_to_element) -- simplifies use
		    char *path = malloc(SIZE+1);
            strcpy(path,add(dry,el_name));

			// Is element information readable ?
		    if (stat(path,&st_element)==0) {

				// Is element a file or a directory and does it match criterias ?
		        if (check(&st_element,ino,max,min,m)>-1 && !S_ISDIR(st_element.st_mode)) {

		            int i;
                    for ( i = 1; i<DTH-depth+1; i++) {

						// Indent display
						printf("|   ");

					}

					// Display file + file information
		            printf("%s -- %llu -- %ld -- %s\n",el_name,st_element.st_ino,(long)st_element.st_size,tvr(&st_element));

		        } else if (S_ISDIR(st_element.st_mode)) {
					// Is element a directory ?

		            int i;
					for (i = 1; i<DTH-depth+1; i++) {

						// Indent display
						printf("|   ");

					}

					// Display directory
                    printf("%s >",el_name);

					// While depth was not reached
					if ((depth-1) != 0) {

						// Recursive Execution
						printf("\n");
                        find(path,depth-1,ino,max,min,m);

					} else {

						// Display if depth was reached
                        printf(" -- Depth reached\n");

					}

				}

			} else {

				fprintf(stderr, "Failed : Unable to open this directory : %s\n", path);
                perror("Failed : Unable to open this directory ");

			}

        }

    }

	// Close directory - if directory is not closed, system will block execution of finder because of too many files opened
    closedir(directory);

    return f;

}
