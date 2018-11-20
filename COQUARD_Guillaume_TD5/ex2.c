// © Guillaume COQUARD, April 2018

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define _WCT_ O_WRONLY | O_CREAT | O_TRUNC
#define _RNB_ O_RDONLY | O_NONBLOCK
#define _WNB_ O_WRONLY | O_NONBLOCK
#define _R_ O_RDONLY
#define _W_ O_WRONLY
#define _ALL_ 0777

int cat(int d, int s);
int sendToPipe(char *d);
int receiveFromPipe(char *s);

int main(int argc, char **argv) {

	char *m = malloc(sizeof(char)*64);
	strcpy(m, "main.fifo");

	if (mkfifo(m, S_IRWXU) != 0) {
		unlink(m);
		mkfifo(m, S_IRWXU);
	}

	if (sendToPipe(m)) receiveFromPipe(m);

	unlink(m);
}

int cat(int d, int s) {
	char *c = "cat.fifo";
	pid_t p = 0;
	int r, w;

	if (mkfifo(c, S_IRWXU) != 0) {
		unlink(c);
		mkfifo(c, S_IRWXU);
	}

	char a, b;

	if ((p = fork()) > 0) {
		w = open(c, _W_);
		while (read(s, &a, 1) > 0) write(w, &a, 1);
		close(w);
	} else if (p == 0) {
		r = open(c, _R_);
		while (read(r, &b, 1) > 0) write(d, &b, 1);
		close(r);
		unlink(c);
		exit(EXIT_SUCCESS);
	} else {
		perror("Fork failed ");
		exit(EXIT_FAILURE);
	}
	return 1;
}

int sendToPipe(char *d) {
	int r , w ;
	if ((r = open(d, _RNB_)) == -1) perror("Pipe : Read-end : Open failed ");
	if ((w = open(d, _WNB_)) == -1) perror("Pipe : Write-end : Open failed ");

	printf("Input : \nYou must finish by hitting ENTER then CTRL+D\n");

	char in;
	while (read(0, &in, 1) == 1) write(w, &in, 1);

	close(w);

	printf("\nInput : Sent to pipe.\n");

	return (1);
}

int receiveFromPipe(char *s) {
	int r, b, t = 0;
	char a, o = '\0', *n = malloc(sizeof(char)*64);
	printf("Would you save input in file ? [Y/N]\n > ");
	scanf("%[^\n]c", &a);
	getchar();
	switch (a) {
		case 'y' : case 'Y' : case '1' :
			b = 1;
			printf("Path to target file : \n");
			scanf("%64[^\n]s",n);
			getchar();
			break;
		case 'n' : case 'N' : case '0' :
			b = 0;
			break;
		default:
			b = 1;
			printf("Path to target file : \n");
			scanf("%64[^\n]s",n);
			getchar();
			break;
	}

	if ((r = open(s, _RNB_)) == -1) perror("Pipe : Read-end : Open failed ");

	if (b) {
		b = open(n, _WCT_, _ALL_);
		cat(b,r);
		close(b);
		close(r);
		t = 1;
	}

	printf("Output : Source : %s : \n", (t?"file :\nNOTICE : The whole file won't be printed":"pipe"));
	if (t) {
		t = open(n, _R_);
		while ((read(t, &o, 1) == 1)) write(1, &o, 1);
	} else {
		while (read(r, &o, 1) == 1) write(1, &o, 1);
	}
	printf("\n");
	close(r);
	return (1);
}
