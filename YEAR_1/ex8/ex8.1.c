//
//  deuxTroisCinq.c
//
//  Created by Guillaume COQUARD on 06/04/2017.
//	Modified last by Guillaume COQUARD on 22/04/2017.
//  Copyright © 2017 Guillaume COQUARD. All rights reserved.
//

#include <stdio.h>

int d, t, c;



// Puissance
int dePetEaN(int p, int e) {
	int i, q = p;
	for (i = 1; i<e; i++) {
		q *= p;
	}
	return q;
}

// Procedure 1
void procedure1() {
	int p, e;
	printf("p ? ");
	scanf("%d", &p);
	printf("e ? ");
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
	printf("n ? ");
	scanf("%d", &n);
	printf("p ? ");
	scanf("%d", &p);
	printf("%d est divisible %d fois par %d.", n, deNetPaE(n, p), p);
	printf("\n");
}



// Lire D T C
void lireDTC() {
	printf("d ? ");
	scanf("%d", &d);
	printf("t ? ");
	scanf("%d", &t);
	printf("c ? ");
	scanf("%d", &c);
}

// Nombre 2d3t5c
int deDTCaN() {
	int res = dePetEaN(2, d)*dePetEaN(3, t)*dePetEaN(5, c);
	return res;
}

// Affichage Chaine
void afficheDTC(int d, int t, int c) {
	printf("2^%d 3^%d 5^%d ", d, t, c);
}

// Procédure 3
void procedure3() {
	lireDTC();
	afficheDTC(d,t,c);
	printf("= %d", deDTCaN());
	printf("\n\n");
}



// deNaDTC
int deNaDTC() {
	int n;
	printf("n ? ");
	scanf("%d", &n);
	return 0;
}


int main() {
	procedure3();
	return 0;
}
