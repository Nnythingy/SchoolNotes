// EvalBoolean.c
#include <stdio.h>

int main(void) {    
	int x, y, z, a = 4, b = -2, c = 0;

	x = (a > b || b > c && a == b);
	printf("x = %d\n", x);

	y = ((a > b || b > c) && a == b);
	printf("y = %d\n", y);

	z = ((a > b) && !(b > c));
	printf("z = %d\n", z);

	return 0;
}

