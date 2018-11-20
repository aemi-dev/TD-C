#include <stdio.h>

int main() {
	printf("Exercise 3 : Permutation\n");
	int a,b;
	printf("a = ");
	scanf("%d",&a);
	printf("b = ");
	scanf("%d",&b);
	b = a+b;a = b-a;b = b-a; // Permutation Steps
	printf("b = a+b;\na = b-a;\nb = b-a;\n");
	printf("a = %d\nb = %d\n\n", a,b);
	return (0);
}
