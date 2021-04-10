#include <stdio.h>

int main() {
	printf("Exercise 4 : Parite oblige\n");
	int a;
	printf("Enter an integer : ");
	scanf("%d", &a);
	a%2 ? printf("%d is odd.\n\n", a) : printf("%d is even.\n\n", a); // Ternary Operator
	// If a is modulo 2, then a is even because a%2 = 0 = false, else a is odd
	return (0);
}
