#include <stdio.h>

int main() {
	printf("Exercise 6 : Moyenne\n");
	int n;
	printf("Enter number of inputs : ");
	scanf("%d", &n);
	float e,f=0;
	for (int i = 0; i < n; i++) { // n execution of the loop
		printf("Input %d : ", i+1);
		scanf("%f", &e);
		f += e; // add it to f (sum)
	}
	printf("Sum ... : %.3f\n", f); // check if sum is correctly computed
	f /= n;
	printf("Average : %.3f\n\n", f); // prompt the average
	return (0);
}
