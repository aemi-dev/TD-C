#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>



#define ROOT getpgid( getpid( ) )

int pid;

void sleeper( int time );
void parent_handler( int signal );
void child_handler( int signal );



int main ( int argc, char  **argv ) {

	pid = fork();

	// Add Handlers
	if ( pid > 0 ) {
		signal(SIGUSR1,parent_handler);
		signal(SIGUSR2,parent_handler);
	} else if ( pid == 0 ) {
		signal(SIGUSR1,child_handler);
		signal(SIGUSR2,child_handler);
	}

	// Sleep 10 seconds then tell parent to pause me
	if (pid == 0) {
		sleeper( 10 );
		kill(ROOT,SIGUSR1);
		while(1) sleep(1);
	} else {
		wait(&pid);
	}

	return 0;
}

void parent_handler( int signal ) {
	switch(signal) {

		case SIGUSR1 :
		printf( "Parent says : Signal received from child. Let me sleep few (2) seconds !\n" );
		sleeper( 2 );
		kill(pid,SIGUSR1);
		break;

		case SIGUSR2 :
		printf( "Parent says : Signal received from child. Let me sleep few (3) seconds !\n" );
		sleeper( 3 );
		kill(pid,SIGUSR2);
		break;

		default :
		break;
	}
}


void child_handler( int signal ) {
	switch(signal) {

		case SIGUSR1 :
		printf( "Child says : Signal received from parent. Let me take a pause !\n" );
		kill(ROOT,SIGUSR2);
		pause();
		break;

		case SIGUSR2 :
		printf( "Child says : Signal received from parent. I woke up !\n" );
		raise(SIGINT);
		break;

		default :
		break;
	}
}


void sleeper( int time ) {
	for ( int i = 0 ; i < time ; i++ ) {
		fflush(stdout);
		printf( ". " );
		sleep(1);
	}
	printf("\n");
}
