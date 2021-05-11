// DataTypes.c
// This program checks the memory size of each of the basic data types
#include <stdio.h>

int main(void) {

	printf("Size of 'int' (in bytes): %d\n", sizeof(int));
	printf("Size of 'float' (in bytes): %d\n", sizeof(float));
	printf("Size of 'double' (in bytes): %d\n", sizeof(double));
	printf("Size of 'char' (in bytes): %d\n", sizeof(char));

	return 0;
}
