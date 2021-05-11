// ArrayModify.c
#include <stdio.h>

void modifyArray(float [], int);
void printArray(float [], int);

int main(void) {
	float num[4] = {3.1, 5.9, -2.1, 8.8}; 

	modifyArray(num, 4);
	printArray(num, 4);

	return 0;
}

void modifyArray(float arr[], int size) {
	int i;

	for (i=0; i<size; i++) {
		arr[i] *= 2;
	}	
}

void printArray(float arr[], int size) {
	int i;

	for (i=0; i<size; i++) {
		printf("%.2f ", arr[i]);
	}
	printf("\n");
}

