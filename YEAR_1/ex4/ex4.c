//
//  continue2.c
//
//  Created by Guillaume COQUARD & Laureline DE JESUS on 23/02/2017.
//  Copyright © 2017 Guillaume COQUARD & Laureline DE JESUS. All rights reserved.
//

#include <stdio.h>

int main() {
	char a,b;
	do {
		do {
			printf("0:quitter\nautre:continuer\n");
			scanf("%c",&a);
		} while(a==' ');
		do {
			scanf("%c",&b);
		} while(b!='\n');
	} while(a!='0');
	printf("\n");
	return 0;
}
