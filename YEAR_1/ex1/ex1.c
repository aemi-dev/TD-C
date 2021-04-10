//
//  etudiants.c
//
//  Created by Guillaume COQUARD & Laureline DE JESUS on 18/01/2017.
//  Copyright © 2017 Guillaume COQUARD & Laureline DE JESUS. All rights reserved.
//

#include <stdio.h>

int main() {
    float m, n;
    printf("nombre d'étudiants inscrits ? ");
    scanf("%f", &m);
    printf("nombre d'étudiants inscrits = %3.0f\n", m);
    printf("nombre d'étudiants présents ? ");
    scanf("%f", &n);
    printf("nombre d'étudiants présents = %3.0f\n", n);
    float pourcentage = n/m*100;
    printf("pourcentage de presences = %2.1f\n", pourcentage);
    return (0);
}
