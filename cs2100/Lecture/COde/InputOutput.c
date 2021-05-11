// InputOutput.c
// Demonstrate scanf() and printf() functions
#include <stdio.h>

int main(void) {
	int age;
	double cap;

	printf("What is your age? ");
	scanf("%d", &age);
	printf("What is your CAP? ");
	scanf("%lf", &cap);
	printf("You are %d years old, and your CAP is %f\n", age, cap);

	return 0;
}

