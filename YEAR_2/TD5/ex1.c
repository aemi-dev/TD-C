// © Guillaume COQUARD, April 2018


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define ROOT (getpgid(getpid()) == getpid())

void copy(char *a, int b);
int copy_files(const char *src, const char *dest);

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Use : ./ex1.out <source> <destination>\n");
		return 1;
	}
	if (ROOT) {
		printf("UNAMED PIPE : \n");
		copy("abcdefghijklmnopqrstuvwxyz",0);
	}
	if (ROOT) {
		printf("\n\n\nNAMED PIPE : \n");
		copy("abcdefghijklmnopqrstuvwxyz",1);
	}
	if (ROOT) {
		if (copy_files(argv[1],argv[2])) {
			if (ROOT) {
				printf("\n\n\nFile Copy : %s to %s\nCopy done.\n\n\n\n",argv[1],argv[2]);
			}
		}
	}
	return (0);
}

void copy(char a[], int b) {
	size_t alen = strlen(a);
	pid_t cpid = 0;
	char buf_0[1], buf_1[1], res_0[alen], res_1[alen], res_2[alen], res_3[alen];
	strcpy(buf_0,"");
	strcpy(buf_1,"");
	strcpy(res_0,"");
	strcpy(res_1,"");
	strcpy(res_2,"");
	strcpy(res_3,"");
	if (b == 0 && (getpid() == getpgid(getpid()))) {
		int p1[2], p2[2];
		pipe(p1);
		pipe(p2);
		char *cur = malloc(sizeof(char));
		cpid = fork();
		for (int i = 0; i < alen; i++) {
			strcpy(cur,"");
			cur[0] = a[i];
			if (cpid == 0) {
				close(p1[0]);
				write(p1[1],cur,1);
			}
			if (cpid > 0) {
				close(p1[1]);
				read(p1[0],buf_1,1);
				strcat(res_1,buf_1);
				printf("pipe - pid : %d - alphabet : %s\n", getpid(), res_1);
				close(p2[0]);
				write(p2[1],buf_1,1);
			}
			if (cpid == 0) {
				close(p2[1]);
				read(p2[0],buf_0,1);
				strcat(res_0,buf_0);
				printf("pipe - pid : %d - alphabet : %s\n", getpid(), res_0);
			}
		}
		if (cpid != 0) {
			printf("pid : %d\nresult : %s\n", getpid(), res_1);
		} else {
			printf("pid : %d\nresult : %s\n", getpid(), res_0);
		}
	} else if (b != 0 && (getpid() == getpgid(getpid()))) {
		char *fifo_name = "pipe_copy.fifo";
		if (mkfifo(fifo_name, S_IRWXU) != 0) {
			unlink(fifo_name);
			if (mkfifo(fifo_name, S_IRWXU) != 0) {
				perror("mkfifo() error");
			}
		}
		int fifo_read, fifo_write;
		cpid = fork();
		char cur[1] = "";
		for (int i = 0; i < strlen(a); i++) {
			cur[0] = a[i];
			if (cpid == 0) {
				fifo_write = open(fifo_name, O_WRONLY);
				write(fifo_write, cur, 1);
				close(fifo_write);
			}
			if (cpid > 0) {
				fifo_read = open(fifo_name, O_RDONLY);
				read(fifo_read, buf_1, 1);
				strcat(res_3,buf_1);
				printf("fifo - pid : %d - alphabet : %s\n", getpid(), res_3);
				close(fifo_read);
				fifo_write = open(fifo_name, O_WRONLY);
				write(fifo_write, cur, 1);
				close(fifo_write);
			}
			if (cpid == 0) {
				fifo_read = open(fifo_name, O_RDONLY);
				read(fifo_read, buf_0, 1);
				strcat(res_2,buf_0);
				printf("fifo - pid : %d - alphabet : %s\n", getpid(), res_2);
				close(fifo_read);
			}
		}
		unlink(fifo_name);
		if (cpid != 0) {
			printf("pid : %d\nresult : %s\n", getpid(), res_3);
		} else {
			printf("pid : %d\nresult : %s\n", getpid(), res_2);
		}
	}
}

int copy_files(const char *src, const char *dest) {
	char *fifo_name = "pipe_files.fifo";
	pid_t cfpid = 0;
	int source, destination, fifo_r, fifo_w;

	/* Create input file descriptor */
	if ((source = open(src, O_RDONLY)) == -1) {
		perror("Source unavailable ");
		return 0;
	}

	/* Create output file descriptor */
	if((destination = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1){
		perror("Destination ");
		return 0;
	}

	if (mkfifo(fifo_name, S_IRWXU) != 0) {
		unlink(fifo_name);
		if (mkfifo(fifo_name, S_IRWXU) != 0) {
			perror("mkfifo() error");
		}
	}

	if ((cfpid = fork()) == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	char *buf1 = malloc(sizeof(char)),*buf2 = malloc(sizeof(char));

	if (cfpid == 0) {
		fifo_r = open(fifo_name, O_WRONLY);
		while (read(source, buf1, 1) > 0) {
			write(fifo_r, buf1, 1);
		}
		close(fifo_r);
	} else if (cfpid > 0) {
		fifo_w = open(fifo_name, O_RDONLY);
		while(read(fifo_w, buf2, 1) > 0) {
			write(destination, buf2, 1);
		}
		close(fifo_w);
		unlink(fifo_name);
	}
	return 1;
}
