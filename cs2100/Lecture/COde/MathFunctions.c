// MathFunctions.c 
#include <stdio.h>
#include <math.h>

int main(void) {    
	int   x, y;
	float val;

	printf("Enter x and y: ");
	scanf("%d %d", &x, &y);
	printf("pow(%d,%d) = %f\n", x, y, pow(x,y));

	printf("Enter value: ");
	scanf("%f", &val);
	printf("sqrt(%f) = %f\n", val, sqrt(val));

	return 0;
}

