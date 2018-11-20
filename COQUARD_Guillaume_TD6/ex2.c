/*
signal() function manage system behavior when a process receive a signal.

signal() function signature is :
void signal( int signum, sighandler_t handler )

signum is the signal, and handler define the way how the signal has to be managed.
handler can be : SIG_DFL || SIG_IGN || (*func)


looper() function allows user to send ten signals to program before exit.
It makes program sleeping.

*/


#include <stdio.h>
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
	printf( "\nSIGNAL : %d\nPID : %d\nDESC : %s\n", signal, (int)getpid(), sys_siglist[signal] );
}

void looper( void ) {
	int i = 10;
	while ( i > 0 ) {
		pause( );
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
