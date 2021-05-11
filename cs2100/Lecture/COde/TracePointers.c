// TracePointers.c
#include <stdio.h>

int main(void) {
	int a = 8, b = 15, c = 23;
	int *p1, *p2, *p3;

	p1 = &b;
	p2 = &c;
	p3 = p2;

	printf("1: %d %d %d\n", *p1, *p2, *p3);

	*p1 *= a;
	while (*p2 > 0) {
		*p2 -= a;
		(*p1)++;
	}

	printf("2: %d %d %d\n", *p1, *p2, *p3);
	printf("3: %d %d %d\n", a, b, c);

	return 0;
}

