//
//  plat.c
//
//  Created by Guillaume COQUARD on 19/02/2017.
//  Copyright © 2017 Guillaume COQUARD. All rights reserved.
//


#include <stdio.h>

int main() {
    int sale, sucre, chaud, cher;
    printf("Ce programme vous permet de saisir si un plat est salé, sucré, chaud, cher à l'aide de variables booléennes. Si le critère est valide, saisissez 1, sinon 0.\n - 1 : Oui\n - 0 : Non\n");
    printf("Le plat est-il salé .... > ");
    scanf("%d", &sale);
    printf("Le plat est-il sucré ... > ");
    scanf("%d", &sucre);
    printf("Le plat est-il chaud ... > ");
    scanf("%d", &chaud);
    printf("Le plat est-il cher .... > ");
    scanf("%d", &cher);
    if (!sale && sucre && !chaud && !cher) {
        printf(":-D\n");
    } else if (sale && !sucre && chaud) {
        printf(":-)\n");
    } else if (!sale && !sucre && !chaud) {
        printf(":-/\n");
    } else if (sale && sucre && !chaud) {
        printf(":-(\n");
    }else if (sale && sucre && chaud && !cher) {
        printf(":-|\n");
    } else {
        printf(":-|");
    }
    return 0;
}
