#include <stdio.h>

int main() {
	printf("Enter two numbers to calculate their PGCD and PPCM :\n");
	int a,b,c,d, pgcd,ppcm;
	printf("a : ");scanf("%d", &a);
	printf("b : ");scanf("%d", &b);
	c=a;d=b;
	while (c!=d) {
		c>d ? (c=c-d) : (d=d-c); // ternary operator to compute substract pgcd algorithm in a loop
	}
	pgcd = c;
	ppcm = (a*b)/pgcd;
	printf("PGCD of %d and %d : %d\nPPCM of %d and %d : %d\n\n", a,b,pgcd,a,b,ppcm);
	return (0);
}
