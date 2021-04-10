//
//  Compress Tool
//
//  Created by Guillaume COQUARD on 08/03/2018.
//  Copyright © 2018 Guizilla. All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

#define S_F  8
#define S_FS 256

int cmp(char *a,char *b);

int main(int argc, char * argv[]) {

	char *ext_char = malloc(2*sizeof(char));
	strcpy(ext_char,".");
	char *cmd = malloc(S_FS*sizeof(char));
	char *format = malloc(S_F*sizeof(char));
	char *file_path = malloc(S_FS*sizeof(char));
	char *file_dest = malloc(S_FS*sizeof(char));

	if (argc<=4) {
		if (argc==2) {
			strcpy(file_path,argv[1]);
			strcpy(format,".tar.gz");
			strcpy(cmd,"tar -zcvf ");
		} else if (argc==3){
			if (cmp(argv[1],"Zip") || cmp(argv[1],"zip")) {
				strcpy(format,".zip");
				strcpy(cmd,"zip -X ");
			} else if (cmp(argv[1],"Bzip") || cmp(argv[1],"Bzip2") || cmp(argv[1],"bzip") || cmp(argv[1],"bzip2") || cmp(argv[1],"bz2") || cmp(argv[1],"bz") || cmp(argv[1],"tar.bz2")) {
				strcpy(format,".tar.bz2");
				strcpy(cmd,"tar -jcvf ");
			} else {
				strcpy(format,".tar.gz");
				strcpy(cmd,"tar -zcvf ");
			}
			strcpy(file_path,argv[2]);
		}
	}
	strcpy(file_dest,file_path);
	int b = 0;
	for (b = (int)strlen(file_path)-1; b>0; b--) {
		if (file_path[b]==ext_char[0] && strlen(file_path)-b<5) {
			b++;
			for (;b<strlen(file_path);b++) {
				file_dest[b]='\0';
			}
			break;
		}
	}
	strcat(file_dest,format);
	strcat(cmd, " ");strcat(cmd,file_dest);
	strcat(cmd, " ");strcat(cmd, file_path);
	system(cmd);
	return (0);
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
