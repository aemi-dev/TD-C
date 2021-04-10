//
//  euro.c
//
//  Created by Guillaume COQUARD & Laureline DE JESUS on 09/02/2017.
//  Copyright © 2017 Guillaume COQUARD & Laureline DE JESUS. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int main() {
    float montant;
    
    int pc1 = 0;
    int pc2 = 0;
    int pc5 = 0;
    int pc10 = 0;
    int pc20 = 0;
    int pc50 = 0;
    
    int pe1 = 0;
    int pe2 = 0;
    
    int b5 = 0;
    int b10 = 0;
    int b20 = 0;
    int b50 = 0;
    int b100 = 0;
    int b200 = 0;
    int b500 = 0;
    
    int tmp;
    
    printf("Saisir un montant en euros : ");
    scanf("%f",&montant);
    printf("Montant saisi : %.2f €\n", montant);
    montant += 0.001;
    
    tmp = montant/500;
    if (tmp > 0) {
        b500 = tmp;
        montant = montant-(b500*500);
        printf("Nombre de billets de 500 euros : %d\n", b500);
    }
    
    tmp = montant/200;
    if (tmp > 0) {
        b200 = tmp;
        montant = montant-(b200*200);
        printf("Nombre de billets de 200 euros : %d\n", b200);
    }
    
    tmp = montant/100;
    if (tmp > 0) {
        b100 = tmp;
        montant = montant - (100*b100);
        printf("Nombre de billets de 100 euros : %d\n", b100);
    }
    
    tmp = montant/50;
    if (tmp > 0) {
        b50 = tmp;
        montant = montant - (50*b50);
        printf("Nombre de billets de 50 euros : %d\n", b50);
    }
    
    tmp = montant/20;
    if (tmp > 0) {
        b20 = tmp;
        montant = montant - (20*b20);
        printf("Nombre de billets de 20 euros : %d\n", b20);
    }

    tmp = montant/10;
    if (tmp > 0) {
        b10 = tmp;
        montant = montant - (10*b10);
        printf("Nombre de billets de 10 euros : %d\n", b10);
    }

    tmp = montant/5;
    if (tmp > 0) {
        b5 = tmp;
        montant = montant - (5*b5);
        printf("Nombre de billets de 5 euros : %d\n", b5);
    }
    
    tmp = montant/2;
    if (tmp > 0) {
        pe2 = tmp;
        montant = montant - (2*pe2);
        printf("Nombre de pieces de 2 euros : %d\n", pe2);
    }
    
    tmp = montant/1;
    if (tmp > 0) {
        pe1 = tmp;
        montant = montant - (1*pe1);
        printf("Nombre de pieces de 1 euro : %d\n", pe1);
    }
    
    tmp = montant/0.50;
    if (tmp > 0) {
        pc50 = tmp;
        montant = montant - (0.50*pc50);
        printf("Nombre de pieces de 50 centimes : %d\n", pc50);
    }
    
    tmp = montant/0.20;
    if (tmp > 0) {
        pc20 = tmp;
        montant = montant - (0.20*pc20);
        printf("Nombre de pieces de 20 centimes : %d\n", pc20);
    }
    
    tmp = montant/0.10;
    if (tmp > 0) {
        pc10 = tmp;
        montant = montant - (0.10*pc10);
        printf("Nombre de pieces de 10 centimes : %d\n", pc10);
    }

    tmp = montant/0.05;
    if (tmp > 0) {
        pc5 = tmp;
        montant = montant - (0.05*pc5);
        printf("Nombre de pieces de 5 centimes : %d\n", pc5);
    }
    
    tmp = montant/0.02;
    if (tmp > 0) {
        pc2 = tmp;
        montant = montant - (0.02*pc2);
        printf("Nombre de pieces de 2 centimes : %d\n", pc2);
    }
    
    tmp = montant/0.01;
    if (tmp > 0) {
        pc1 = tmp;
        montant = montant - (0.01*pc1);
        printf("Nombre de pieces de 1 centime : %d\n", pc1);
    }
    return 0;
}
