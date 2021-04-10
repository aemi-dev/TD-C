// © Guillaume COQUARD, April 2018

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Use : ./ex4.out <int number_of_seconds>\n");
		return 1;
	}

	int p[2], d;

	pipe(p);

	if ((d = fork()) == 0) {
		int i = 0;
		while(sleep(1) == 0) {
			printf(". ");
			i++;
			close(p[0]);
			write(p[1], &i, sizeof(int));
			fflush(NULL);
		}
	} else {
		int t;
		sleep(atoi(argv[1]));
		sleep(0);
		kill(d,SIGKILL);
		close(p[1]);
		while(read(p[0], &t, sizeof(int)));
		printf(": Seconds : %d\n", t);
	}
	return 0;
}
