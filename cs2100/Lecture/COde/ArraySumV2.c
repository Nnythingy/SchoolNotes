// ArraySumV2.c
#include <stdio.h>
#define MAX 5

int main(void) {
	int numbers[MAX] = { 4, 12, -3, 7, 6 };
	int i, sum = 0;

	for (i=0; i<MAX; i++) {
		sum += numbers[i];
	}

	printf("Sum = %d\n", sum);
	return 0;
}

