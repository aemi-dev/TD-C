#include <stdio.h>
#include <math.h>

// Necessary to use sqrt() : add -lm at end of compiling command in terminal

int main() {
	int a, b, c, d; // a b c d are integer in every possible case
	float e, f, g; // e f g are results, so they are float
	printf("Enter 3 values for a,b,c in : a(x^2) + bx + c = 0 : \n");
	printf("a : ");scanf("%d", &a);
	printf("b : ");scanf("%d", &b);
	printf("c : ");scanf("%d", &c);
	d = b*b - 4*a*c; // delta = b^2 - 4ac
	if (a!=0) { // check if function is affine
		if (d<0) {
			printf("Equation does not accept any real solutions. They should be imaginary solutions.\n\n");
		} else if (d>0) {
			e = (-b+sqrt(d))/((2.0)*a); // solve the 2 solutions if delta positive
			f = (-b-sqrt(d))/((2.0)*a); // use 2.0 to make integer division a float division
			printf("Equation : %d(x^2)+%dx+%d = 0 : has two solutions :\nx1 : %.4f\nx2 : %.4f\n\n", a,b,c,e,f);
		} else {
			e = (-b)/((2.0)*a); // solve one solution because delta is null
			printf("Equation : %d(x^2)+%dx+%d = 0 : has one solution :\nx : %.4f\n\n", a,b,c,e);
		}
	} else {
		g = (-c/(b*1.0)); // solve if function is affine
		printf("Equation : %d(x^2)+%dx+%d = 0 : has one solution :\nx : %.4f\n\n", a,b,c,g);
	}
	return (0);
}
