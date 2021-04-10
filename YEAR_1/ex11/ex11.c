//
//  conway.c
//
//  Created by Guillaume COQUARD on 27/04/2017.
//  Copyright © 2017 Guillaume COQUARD. All rights reserved.
//	Software : Apple Xcode 8.3.2 (8E2002)
//


#include <stdio.h>


// Constants
#define S 20	// SIDE


int A[S][S][1];	// DISPLAY
int B[S][S][1];	// CALC
int C[S][S][1];	// NB NB // USELESS
int D[S][S][1];	// AL NB
int E;			// HOR POS
int	F;			// VER POS


void display(int d) {
	int e, f, g = 1;
	for (e = 0; e < S; e++) {
		for (f = 0; f < S; f++) {
			if (d == 0) {
				if (A[e][f][0] == 0) {
					printf(" ");
				} else {
					printf("O");
				}
			} else if (d == 1) {
				if (B[e][f][0]==0 && A[e][f][0]==0) {
					printf(" ");
				} else if (B[e][f][0]==0) {
					printf("X");
				} else if (B[e][f][0]==1) {
					printf("N");
				} else if (B[e][f][0]==2) {
					printf("O");
				}
			} else if (d == 2) {
				printf("%d", C[e][f][0]);
			} else if (d == 3) {
				printf("%d", D[e][f][0]);
			}
			printf(" ");
			if ((g)%S == 0 && g!=(0)) {
				printf("\n");
			}
			g++;
		}
	}
	printf("\n");
}


int detS(int j, int k) {
	if (j == 0 && k == 0) {
		return 0;
	} else if (j == S-1 && k == 0) {
		return 1;
	} else if (j == S-1 && k == S-1) {
		return 2;
	} else if (j == 0 && k == S-1) {
		return 3;
	} else if (j == 0 && (k>0 && k<S-1)) {
		return 10;
	} else if (j == S-1 && (k>0 && k<S-1)) {
		return 11;
	} else if ((j>0 && j<S-1) && k == 0) {
		return 12;
	} else if ((j>0 && j<S-1) && k == S-1) {
		return 13;
	} else {
		return -1;
	}
}


void detN(int h, int i) { // USELESS //
	if ((h == 0 && i == 0)||(h == S-1 && i == 0)||(h == S-1 && i == S-1)||(h == 0 && i == S-1)) {
		C[h][i][0] = 3;
	} else if ((h == 0 && (i>0 && i<S-1))||(h == S-1 && (i>0 && i<S-1))||((h>0 && h<S-1) && i == 0)||((h>0 && h<S-1) && i == S-1)) {
		C[h][i][0] = 5;
	} else if ((h>0 && h<S-1) && (i>0 && i<S-1)) {
		C[h][i][0] = 8;
	}
}


void detA(int l, int m) {
	int n, o, q, r;
	for (n = 0; n < S; n++) {
		for (o = 0; o < S; o++) {
			D[n][o][0] = 0;
		}
	}
	for (n = 0; n < S; n++) {
		for (o = 0; o < S; o++) {
			if (detS(n, o) == 0) {
				q = n+1;
				r = o;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				q = n+1;
				r = o+1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				q = n;
				r = o+1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
			} else if (detS(n, o) == 1) {
				q = n-1;
				r = o;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				q = n-1;
				r = o+1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				q = n;
				r = o+1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
			} else if (detS(n, o) == 2) {
				q = n-1;
				r = o;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				q = n-1;
				r = o-1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				q = n;
				r = o-1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
			} else if (detS(n, o) == 3) {
				q = n+1;
				r = o;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				q = n+1;
				r = o-1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				q = n;
				r = o-1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
			} else if (detS(n, o) == 10) {
				q = n-1;
				r = o;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				for (q = n-1; q <= n+1; q++) {
					r = o+1;
					if (A[q][r][0] == 1) {
						D[n][o][0]++;
					}
				}
				q = n+1;
				r = o;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
			} else if (detS(n, o) == 11) {
				q = n;
				r = o-1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				for (r = o-1; r <= o+1; r++) {
					q = n-1;
					if (A[q][r][0] == 1) {
						D[n][o][0]++;
					}
				}
				q = n;
				r = o+1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
			} else if (detS(n, o) == 12) {
				q = n-1;
				r = o;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				for (q = n-1; q <= n+1; q++) {
					r = o-1;
					if (A[q][r][0] == 1) {
						D[n][o][0]++;
					}
				}
				q = n+1;
				r = o;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
			} else if (detS(n, o) == 13) {
				q = n;
				r = o+1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				for (r = o-1; r <= o+1; r++) {
					q = n+1;
					if (A[q][r][0] == 1) {
						D[n][o][0]++;
					}
				}
				q = n;
				r = o+1;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
			} else {
				for (q = n-1; q <= n+1; q++) {
					r = o-1;
					if (A[q][r][0] == 1) {
						D[n][o][0]++;
					}
				}
				for (q = n-1; q <= n+1; q++) {
					r = o+1;
					if (A[q][r][0] == 1) {
						D[n][o][0]++;
					}
				}
				q = n-1;
				r = o;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
				q = n+1;
				r = o;
				if (A[q][r][0] == 1) {
					D[n][o][0]++;
				}
			}
		}
	}
}


void cpAB() {
	int u, v;
	for (u = 0; u < S; u++) {
		for (v = 0; v < S; v++) {
			B[u][v][0] = A[u][v][0];
		}
	}
}


void cpBA() {
	int w, x;
	for (w = 0; w < S; w++) {
		for (x = 0; x < S; x++) {
			if (B[w][x][0]==0) {
				A[w][x][0] = 0;
			} else if (B[w][x][0]==1||B[w][x][0]==2) {
				A[w][x][0] = 1;
			}
		}
	}
}


void calcDB(int s, int t) {
	if (A[s][t][0] == 0 && D[s][t][0]==3) {
		B[s][t][0]++;
	} else if (A[s][t][0] == 1 && (D[s][t][0]==2 || D[s][t][0]==3)) {
		B[s][t][0]++;
	} else {
		B[s][t][0] = 0;
	}
}


void calcPR() {
	cpAB();
	int y, z;
	for (y = 0; y < S; y++) {
		for (z = 0; z < S; z++) {
			detN(y, z);
			detA(y, z);
			calcDB(y,z);
		}
	}
}


void be_the_god() {
	printf("Choisissez une position verticale : \n(1 => %d) > ", S-2);
	scanf("%d", &F);
	while (F<1 || F>(S-2)) {
		printf(" > ");
		scanf("%d", &F);
	}
	printf("Choisissez une position horizontale : \n(1 => %d) > ", S-2);
	scanf("%d", &E);
	while (E<1 || E>(S-2)) {
		printf(" > ");
		scanf("%d", &F);
	}
}

void wake() {
	A[E-1][F][0] = 1;
	A[E][F-1][0] = 1;
	A[E][F][0] = 1;
	A[E][F+1][0] = 1;
	A[E+1][F][0] = 1;
}


void wakemore() {
	int ad = 0;
	printf("Voulez-vous reveiller d'autres cellules ? \n - [1] : Oui\n - [0] : Non\n > ");
	scanf("%d", &ad);
	if (ad) {
		be_the_god();
		wake();
		display(0);
	}
}


void init(int a) {
	int b, c;
	for (b = 0; b < S; b++) {
		for (c = 0; c < S; c++) {
			A[b][c][0] = a;
			wake();
		}
	}
}


int main() {
	int p = 0, aa = 0, ab, ac;
	printf("Ce programme permet de jouer au jeu de Conway (1970), dont le\nprincipe est expliqué ci-apres.\nOn considère une aire de jeu de 400 cellules.\nA l'origine, toutes sont endormies.\nVous déciderez donc des premières cellules qui se reveilleront.\nL'etat d'une cellule à un cycle dépend de son etat\n au cycle precedent et de celui de ses voisines.\n\n - si la cellule est endormie à ce cycle et que 3 de ses\n   voisines sont eveillees, alors elle sera eveillee au prochain\n   cycle.\n - si la cellule est eveillee à ce cycle et que 2 ou 3 de ses\n   voisines le sont aussi, alors elle sera eveillee au prochain\n   cycle.\n - Dans tous les autres cas la cellule s'endormira au prochain\n   cycle.\n\n\nVoulez-vous jouer ? \n - [1] : Oui\n - [0] : Non\n > ");
	scanf("%d", &aa);
	if (aa) {
		be_the_god();
		init(0);
		display(0);
	}
	while (aa) {
		calcPR();
		display(1);
		cpBA();
		display(0);
		p++;
		printf("\nVoulez-vous continuer ? \n - [1] : Oui\n - [0] : Non\n > ");
		scanf("%d", &aa);
		if (aa) {
			wakemore();
			cpAB();
			for (ab = 0; ab < S; ab++) {
				for (ac = 0; ac < S; ac++) {
					detA(ab, ac);
				}
			}
		}
	}
	printf("La vie a perduré pendant %d cycles.\n\n", p);
	return 0;
}
