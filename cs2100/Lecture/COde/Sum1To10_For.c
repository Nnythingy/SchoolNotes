// Sum1To10_For.c
#include <stdio.h>

int main(void) {    
	int sum, i;
	for (sum = 0, i = 1; i <= 10; i++) {
		sum = sum + i;
	}

	printf("sum = %d\n", sum);

	return 0;
}

