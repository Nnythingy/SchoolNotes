// StringIO1.c 
#include <stdio.h>
#define LENGTH 10

int main(void) {
	char str[LENGTH];

	printf("Enter string (at most %d characters): ", LENGTH-1);
	scanf("%s", str); 

	printf("str = %s\n", str); 

	return 0;
}

