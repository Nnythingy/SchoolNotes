// ArraySumFunction.c
#include <stdio.h>

int sumArray(int [], int);

int main(void) {
	int val[6] = {44, 9, 17, -4, 22};
	printf("Sum = %d\n", sumArray(val, 6));
	return 0;
}

// To sum up values in array arr
int sumArray(int arr[], int size) {
	int i, sum=0;

	for (i=0; i<size; i++) {
		sum += arr[i];
	}
	return sum;
}

