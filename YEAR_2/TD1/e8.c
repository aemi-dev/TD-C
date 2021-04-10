#include <stdio.h>

int main() {
	printf("Exercise 8 : Arithmetique de base\n");
	int a;
	float b,c;
	char o,bin;
	printf("Enter number of inputs : ");
	scanf("%d", &a);
	printf("Enter operator [+,-,*,/] : ");
	scanf("%c", &bin);
	scanf("%c", &o);
	for (int i = 0; i < a; i++) {
		printf("Enter a number : ");
		if (i==0) {
			scanf("%f", &b);
		} else {
			scanf("%f", &c);
			switch (o) { // switch condition to avoid lot of if-then-else
				case '+' :
				b += c;
				break;
				case '-' :
				b -= c;
				break;
				case '*' :
				b *= c;
				break;
				case '/' :
				while (c==0) { // in case of entering 0 for c because b/c when c = 0 is impossible
					printf("0-division impossible. Enter an other number : ");
					scanf("%f", &c);
				}
				b /= c;
				break;
				default :
				break;
			}
		}
	}
	printf("Result : %.5f\n\n", b);
	return (0);
}
