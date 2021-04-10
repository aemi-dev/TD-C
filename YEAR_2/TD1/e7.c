#include <stdio.h>

int main() {
	printf("Exercise 7 : Un peu de maths\n");
	int n,s=0;
	printf("Enter number of integer : ");
	scanf("%d", &n);
	printf("Sum of %d first integers : ", n);
	for (int i = 0; i < n ; i++) { // 0 + 1 + 2 + ... + n-1
		s+=i;
	}
	printf("%d\n\n",s);
	return (0);
}
