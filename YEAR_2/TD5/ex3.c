// © Guillaume COQUARD, April 2018

#include <stdio.h>
#include <unistd.h>

int main() {
	int p[2];
	pipe(p);
	if (!fork()) {
		close(STDIN_FILENO);
		dup(p[0]);
		close(p[1]);
		execlp("wc","wc","-l",NULL);
	} else {
		close(STDOUT_FILENO);
		dup(p[1]);
		close(p[0]);
		execlp("ls","ls","-al",NULL);
	}
	return (0);
}
