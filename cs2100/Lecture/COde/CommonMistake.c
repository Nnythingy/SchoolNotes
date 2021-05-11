// CommonMistake.c 
#include <stdio.h>

int main(void) {
	int *n;

	*n = 123;
	printf("%d\n", *n);

	return  0;
}

