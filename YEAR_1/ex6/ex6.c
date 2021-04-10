//
//  factorielle.c
//
//  Created by Guillaume COQUARD on 23/03/2017.
//  Copyright © 2017 Guillaume COQUARD. All rights reserved.
//

#include <stdio.h>

int recursive(int n) {
    int r = 1;
    if (n != 0) {
        r = n * recursive(n-1);
    }
    return r;
}


int iterative(int n) {
    int r = 1;
    if (n != 0) {
        for (int i = 1; i<=n; i++) {
            r = r * i;
        }
    }
    return r;
}

void ic() {
    char bin = '0';
    scanf("%c", &bin);
}

int main() {
    int n;
    char c;
    
    printf("Quelle factorielle voulez-vous calculer : \n > ");
    scanf("%d", &n);
    ic();
    while (n>=13) {
        printf("Il est impossible de calculer la factorielle de %d.\nLe résultat ne peut pas être enregistré en type 'int'.\nVeuillez ressaisir un nombre inférieur à 13 : \n > ", n);
        scanf("%d", &n);
        ic();
    }
    printf("\n");
    printf("Quelle méthode utiliser : \n\n    [R,r,1] - Récursive\n    [I,i,2] - Itérative\n\n > ");
    scanf("%c", &c);
    ic();
    
    if (((c!='R') && (c!='r') && (c!='1')) && ((c!='I') && (c!='i') && (c!='2'))) {
        printf("Ce n'est pas un choix possible.\nRessaisissez une méthode : \n > ");
        scanf("%c",&c);
        ic();
    }
    printf("\n");
    switch (c) {
        case 'R': case 'r': case '1':
            printf("fact(%d) = %d", n, recursive(n));
            break;
        case 'I': case 'i': case '2':
            printf("fact(%d) = %d", n, iterative(n));
            break;
        default:
            break;
    }
    printf("\n\n");
    return 0;
}

