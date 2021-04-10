//
//  main.c
//  Test_Algo_005
//
//  Created by Guillaume COQUARD on 02/03/2017.
//  Copyright © 2017 Guillaume COQUARD. All rights reserved.
//

#include <stdio.h>

int main() {
    int a = 2; int * p = &a; int b = *p; int c = 8;
    printf("1: a = %d, b = %d, *p = %d.\n", a, b, *p);
    a *= 5;
    printf("2: a = %d, b = %d, *p = %d.\n", a, b, *p);
    b += 1;
    printf("3: a = %d, b = %d, *p = %d.\n", a, b, *p);
    int * q = &b;
    printf("4: a = %d, b = %d, *p = %d, *q = %d.\n", a, b, *p, *q);
    p = q;
    printf("5: a = %d, b = %d, *p = %d, *q = %d.\n", a, b, *p, *q);
    q = &a;
    printf("6: a = %d, b = %d, *p = %d, *q = %d.\n", a, b, *p, *q);
    (*q)++;
    printf("7: a = %d, b = %d, *p = %d, *q = %d.\n", a, b, *p, *q);
    q = &c;
    printf("8: a = %d, b = %d, *p = %d, *q = %d.\n", a, b, *p, *q);
    return 0;
}
