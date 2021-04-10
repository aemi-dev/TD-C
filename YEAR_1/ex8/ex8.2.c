//
//  deuxTroisCinq.c
//
//  Created by Guillaume COQUARD on 06/04/2017.
//  Copyright © 2017 Guillaume COQUARD. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int d;
int t;
int c;


// Puissance
int dePetEaN(int p, int e) {
	int i;
	for (i = 0; i<e; i++) {
		p = p*p;
	}
	return p;
}


// Procedure 1
void procedure1() {
	int p, e;
	printf("p ? \n");
	scanf("%d", &p);
	printf("e ? \n");
	scanf("%d", &e);
	printf("%d^%d = %d", p, e, dePetEaN(p, e));
	printf("\n");
}


// Divisibilité
int deNetPaE(int n, int p) {
	int e = 0;
	while ((n%p)==0) {
		n = n/p;
		e++;
	}
	return e;
}


// Procedure 2
void procedure2() {
	int n, p;
	printf("n ? \n");
	scanf("%d", &n);
	printf("p ? \n");
	scanf("%d", &p);
	printf("%d est divisible %d fois par %d.", n, deNetPaE(n, p), p);
	printf("\n");
}



// Lire D T C
void lireDTC() {
	printf("d ? \n");
	scanf("%d", &d);
	printf("t ? \n");
	scanf("%d", &t);
	printf("c ? \n");
	scanf("%d", &c);
}


// Nombre 2d3t5c
int deDTCaN(int d, int t, int c) {
	return (dePetEaN(2, d)*dePetEaN(3, t)*dePetEaN(3, c));
}


// Affichage Chaine
void afficheDTC(int d, int t, int c) {
	printf("2 %d 3 %d 5 %d ", d, t, c);
}

// Procédure 3
void procedure3() {
	lireDTC();
	afficheDTC(d,t,c);
	printf("= %d", deDTCaN(d,t,c));
}



/////////////
/////////////
/////////////
/////////////
/////////////
/////////////
/////////////



int main() {
	procedure3();
	return 0;
}
