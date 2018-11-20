#include <stdio.h>

int main() {
	printf("Exercise 2 : Cercle\n");
	float a,b,c,pi=3.14159265; // a : radius
	printf("Enter radius : ");
	scanf("%f", &a);
	b = 2*a*pi; // Perimeter
	c = a*a*pi; // Area
	printf("Perimeter : %.5f\nArea : %.5f\n\n", b,c); // %.5f : 5 decimals for a float number
	return (0);
}
