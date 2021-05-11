// PassByValue.c
#include <stdio.h>

void g(int, int);

int main(void) {
	int a = 2, b = 3;

	printf("In main, before: a=%d, b=%d\n", a, b);
	g(a, b);
	printf("In main, after : a=%d, b=%d\n", a, b);
	return 0;
}

void g(int a, int b) {
	printf("In g, before: a=%d, b=%d\n", a, b);
	a = 100 + a;
	b = 200 + b;
	printf("In g, after : a=%d, b=%d\n", a, b);
}

