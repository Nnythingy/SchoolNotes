// ArithOps.c
// To illustrate some arithmetic operations in C
#include <stdio.h>

int main(void) {
	int x, p, n; 

	// to show left associativity
	printf("46 / 15 / 2 = %d\n", 46/15/2);
	printf("19 %% 7 %% 3 = %d\n", 19%7%3);

	// to show right associativity
	x = -23;
	p = +4 * 10;
	printf("x = %d\n", x);
	printf("p = %d\n", p);

	// to show truncation of value
	n = 9 * 0.5;
	printf("n = %d\n", n);

	return 0;
}

