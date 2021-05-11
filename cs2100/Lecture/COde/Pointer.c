// Pointer.c 
#include <stdio.h>

int main(void) {
	double a, *b;

	b = &a;
	*b = 12.34;
	printf("%f\n", a);

	return  0;
}

