// © Guillaume COQUARD, April 2018

#include <stdio.h>
#include <string.h>
#include <signal.h>

int main(int a, char **b) {
	printf("STRSIGNAL : \n");
	for (int i = 1; i < NSIG ; i++) printf("Signal %s\n", strsignal(i));
	printf("\n\nSYS_SIGLIST : \n");
	for (int i = 1; sys_siglist[i]; i++) printf("Signal %d : %s\n", i, sys_siglist[i]);
	return 0;
}
