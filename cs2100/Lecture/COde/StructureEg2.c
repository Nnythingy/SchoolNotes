// StructureEg2.c
#include <stdio.h>

typedef struct  {
	int max;
	float ave;
} result_t;

result_t max_and_average(int, int, int);

int main(void) {
	int num1, num2, num3; 
	result_t result;

	printf("Enter 3 integers: ");
	scanf("%d %d %d", &num1, &num2, &num3);

	result = max_and_average(num1, num2, num3);
	
	printf("Maximum = %d\n", result.max);
	printf("Average = %.2f\n", result.ave);

	return  0;
}

// Computes the maximum and average of 3 integers
result_t max_and_average(int n1, int n2, int n3) {
	result_t result;
	
	result.max = n1;
	if (n2 > result.max)
		result.max = n2;
	if (n3 > result.max)
		result.max = n3;

	result.ave = (n1+n2+n3)/3.0;
	
	return result;
}
