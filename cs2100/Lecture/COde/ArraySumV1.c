// ArraySumV1.c
#include <stdio.h>
#define MAX 5

int main(void) {
	int numbers[MAX];
	int i, sum = 0;

	printf("Enter %d integers: ", MAX);
	for (i=0; i<MAX; i++) {
		scanf("%d", &numbers[i]);
	}

	for (i=0; i<MAX; i++) {
		sum += numbers[i];
	}

	printf("Sum = %d\n", sum);
	return 0;
}

