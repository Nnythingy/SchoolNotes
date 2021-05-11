// SwapIncorrect.c
#include <stdio.h>

void swap(int, int);

int main(void) {
	int a = 2, b = 3;

	printf("In main, before: a=%d, b=%d\n", a, b);
	swap(a, b);
	printf("In main, after : a=%d, b=%d\n", a, b);
	return 0;
}

void swap(int a, int b) {
	int temp = a;
	a = b;
	b = temp;
}

