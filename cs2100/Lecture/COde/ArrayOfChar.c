// ArrayOfChar.c
#include <stdio.h>

void modifyArray(char [], int);
void printArray(char [], int);

int main(void) {
	char chars[4] = {'C', 'h', 'a', 'r'};

	modifyArray(chars, 4);
	printArray(chars, 4);

	return 0;
}

void modifyArray(char arr[], int size) {
	int i;

	for (i=0; i<size; i++) {
		arr[i]++;
	}	
}

void printArray(char arr[], int size) {
	int i;

	for (i=0; i<size; i++) {
		printf("%c", arr[i]);
	}
	printf("\n");
}

