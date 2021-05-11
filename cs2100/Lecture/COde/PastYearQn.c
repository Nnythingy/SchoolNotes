// PastYearQn.c
#include <stdio.h>

int main(void) {    
	int i, n = 2147483640;

	for (i=1; i<=10; i++) {
		n = n + 1;
	}
	printf("n = %d\n", n);

	return 0;
}

