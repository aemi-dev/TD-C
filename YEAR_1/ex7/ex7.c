//
//  romain2arabe.c
//
//  Created by Guillaume COQUARD on 24/03/2017.
//  Copyright © 2017 Guillaume COQUARD. All rights reserved.
//

#include <stdio.h>

char CR[] = "IVXLCDM";
int CA[] = {1, 5, 10, 50, 100, 500, 1000, 1000};

///////////////////////////////////////////////////////////////

int RVA(char * s) {
    int nA = 0, psl = 1;
    int sl = strlen(s);
    
    for (int i = sl-1; i >= 0; i--) {
        int j = 0;
        while((s[i] != CR[j]) && (j < 7)) j++;
        if (CA[j] >= psl) {
            nA += CA[j];
            psl = CA[j];
        }
        else nA -= CA[j];
    }
    return nA;
}

///////////////////////////////////////////////////////////////
int main() {
    char R[100];
    int A;
    printf("Tapez un nombre en chiffres romains \n    %s\n > ", CR);
    scanf("%s", R);
    A = RVA(R);
    printf("Ce nombre ecrit en chiffres arabes est: %d\n", A);
    printf("Au revoir.\n");
    return 0;
}
