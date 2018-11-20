#include <stdio.h>
#include <stdlib.h>

int *eratosthene( int n );
void display( int *a, int length );

int main ( int argc, char **argv ) {

	int a = 0;

	printf("Enter a number : ");

	scanf("%d", &a);

	int *b = eratosthene(a);
	display(b,a);

	return 0;

}


void display( int *a, int length ) {

	for ( int i = 0 ; i < length ; i++ ) {
		printf("%s%d%s", (i==0?"[":", "), (a[i]==0?i:-1), (i==length-1?"]":""));
	}
	printf("\n");
}


int *eratosthene( int n ) {

	int *a = calloc( n, sizeof( int ) );

	for ( int i = 2 ; i < n ; i++ ) {
		for ( int j = i+1 ; j < n ; j++ ) {
			if ( ( a[j] == 0 ) && ( j%i == 0 ) ) {
				a[j] = 1;
			}
		}
	}

	return a;

}
