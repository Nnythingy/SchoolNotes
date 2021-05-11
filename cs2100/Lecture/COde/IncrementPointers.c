// IncrementPointers.c
#include <stdio.h>

int main(void) {
	int a;
	float b;
	char c;
	double d;
	int *ap;
	float *bp;
	char *cp;
	double *dp;

	ap = &a; bp = &b; cp = &c; dp = &d;
	printf("%p %p %p %p\n", ap, bp, cp, dp);

	ap++; bp++; cp++; dp++;
	printf("%p %p %p %p\n", ap, bp, cp, dp);

	ap += 3;
	printf("%p\n", ap);

	return 0;
}

