#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*

/!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\
/!\  PROGRAM DOES NOT WORK  /!\
/!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\

*/


#define ROOT ( getpgid( getpid( ) ) == getpid( ) )


int primeness( int n );


int main ( int argc, char **argv ) {

	int a = 0;

	printf("%d %d %d %d\n", 16/8, 17/8, 15/8, 205/8);
	printf("Enter a number to know his primeness : ");
	scanf("%d", &a);

	printf("%d %s\n", a, (primeness(a)?"is not prime.":"is prime."));
	printf("%d : number of divider\n", primeness(a) );

	return 0;

}


int getSize( int *a ) {
	int b = 1;
	int c = 0;
	for ( int i = 0 ; b ; i++ ) {
		if ( ( i == 0 ) || ( i > 0 && ( ( int )( a[i] ) ) > ( ( int )( a[i-1] ) ) ) ) {
			c++;
		} else {
			b = 0;
		}
	}
	return c;
}


void display( int *a ) {
	printf("[ ");
	for ( int i = 0 ; i < getSize( a ) ; i++ ) {
		printf("%d ", a[i]);
	}
	printf("]\n");
}


int *anteprimes( int n ) {
	int *a = calloc( n, sizeof( int ) );
	for ( int i = 2 ; i < n ; i++ ) {
		for ( int j = i+1 ; j < n ; j++ ) {
			( ( a[j] == 0 ) && ( j%i == 0 ) ) ? a[j] = 1 : 0;
		}
	}
	int *b = calloc( n, sizeof( int ) ), j = 0;
	for ( int i = 0 ; i < n ; i++ ) {
		if ( a[i] == 0 ) {
			b[j] = i;
			j++;
		}
	}
	return b;
}


int *multiplecandidates( int n ) {
	int *a = anteprimes( n ), b = getSize( a ), *c = calloc( b, sizeof( int ) );
	for (int i = 0; ( i < b ) && ( a[i]*a[i] < n ) ; i++ ) c[i] = a[i];
		return c;
}


int primeness( int n ) {
	int *a = multiplecandidates( n ), b = getSize( a ), c = 0;

	int an = ((float)b/(float)8)>(float)((int)(b/8))?(b/8)+1:(b/8);
	int aa[an][8];

	for ( int i = 0 ; i < an ; i++ ) {
		for ( int j = 0 ; j < 8 ; j++ ) {
			aa[i][j] = 0;
		}
	}
	for ( int i = 0 ; i < b ; i++ ) {
		for ( int j = 0 ; j < an ; j++ ) {
			for ( int k = 0 ; k < 8 ; k++ ) {
				aa[j][k] = a[i];
				i++;
			}
		}
	}
	pid_t pid;
	int count = 0;
	int status;
	for ( int i = 0 ; i < an ; i++ ) {
		if ( ROOT ) {
			count++;
			pid = fork();
			waitpid(pid, &status, 0);
		}
	}
	if (getpid() == getpgid(getpid())+count) {
		int integer = 0;
		for (int i = 0 ; i < 8 ; i++ ) {
			if (n%aa[count][i] == 0) {
				integer++;
			}
		}
		exit(integer);
	}
	if ( ROOT && WIFEXITED(status) ) {
		c += WEXITSTATUS(status);
	}

	printf("%d\n", c);

	return c;
}

