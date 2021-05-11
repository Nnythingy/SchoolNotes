// Sum1To10_While.c
#include <stdio.h>

int main(void) {    
	int sum = 0, i = 1;
	while (i <= 10) {
		sum = sum + i;
		i++;
	}

	printf("sum = %d\n", sum);

	return 0;
}

