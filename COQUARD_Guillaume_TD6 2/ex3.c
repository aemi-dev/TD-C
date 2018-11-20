#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void changer( );
void looper( void );
void manager( int signal );

int main( int argc, char **argv ) {
	changer();
	looper();
	return ( 0 );
}

void manager( int signal ) {
	switch(signal) {
		case SIGINT :
		printf("\nProgram is ending. Saving...\n");
		exit(0);
		break;
		default:
		printf( "\nSIGNAL : %d\nPID : %d\nDESC : %s\n", signal, (int)getpid(), sys_siglist[signal] );
		break;
	}
}

void looper( void ) {
	int i = 10;
	while ( i > 0 ) {
		printf("\nProgram paused.\n");
		pause( );
		printf("\nProgram resumed.\n");
		i--;
	}
}

void changer( ) {
	int i;
	for (i = 0; i < NSIG ; i++) {
		if ( signal(i,manager) == SIG_ERR ) {
			fprintf(stderr, "Signal %d cannot be managed.\n", i);
		}
	}
}
