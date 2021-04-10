#include <stdio.h>
#include <stdlib.h>


int primeness( int n );


int main ( int argc, char **argv ) {

	int a = 0;

	printf("Enter a number to know his primeness : ");
	scanf("%d", &a);

	printf("%d %s\n", a, (primeness(a)?"is prime.":"is not prime."));

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
	int *a = multiplecandidates( n ), b = getSize( a ), c = 1;
	for ( int i = 2 ; i < b ; i++ ) {
		if ( n%a[i] == 0 ) {
			c = 0;
			i = b;
		}
	}
	return c;
}

