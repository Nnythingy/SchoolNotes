// TestIO.c
// This program explores the scanf() and printf() functions.
//  * The use of format specifier; what if we use %f on integer, 
//    or %d on float?
//  * What if we enter a real number say 12.3 for variable a?
//  * What if we enter 23.3 for variable f? What is printed?
//    -- This shows that real number cannot be represented accurately.
//  * Experiment with different width specifiers and decimal place specifiers
//    eg: %5.2f, %7.3f, etc.
#include <stdio.h>

int main(void) {

	int a;
	float f;

	printf("Enter an integer: ");
	scanf("%d", &a);  

	printf("Value entered: %d\n", a);

	printf("Enter a real number: ");
	scanf("%f", &f);  
	printf("Value entered: %f\n", f);

	return 0;
}

