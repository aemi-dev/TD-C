#include <stdio.h>

int main() {
	printf("Exercise 5 : X-Factor\n");
	int n;
	long r = 1; // Variable of long type predefined to 1 for n = 0 or n = 1
	printf("Enter an integer : ");
	scanf("%d", &n);
	if (n != (0||1)) {
		for (int i=n ; i>1 ; i--) { // Multiply r by i (equals n) and decrementing i until 1 ==> similar to recursive
			r *= i;
		}
	}
	printf("Factorial of %d : %ld\n\n", n,r);
	return (0);
}
