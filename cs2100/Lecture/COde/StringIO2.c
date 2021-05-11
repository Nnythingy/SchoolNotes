// StringIO2.c 
#include <stdio.h>
#define LENGTH 10

int main(void) {
	char str[LENGTH];

	printf("Enter string (at most %d characters): ", LENGTH-1);
	fgets(str, LENGTH, stdin);

	printf("str = ");
	puts(str);

	return 0;
}

