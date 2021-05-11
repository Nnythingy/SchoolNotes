// Washer.c
#include <stdio.h>
#include <math.h>
#define PI 3.14159

int main(void) {
	double d1, // inner diameter
	       d2, // outer diameter
	       thickness, outer_area, inner_area, rim_area, volume;      

	// read input data
	printf("Enter inner diameter, outer diameter, thickness: ");
	scanf("%lf %lf %lf", &d1, &d2, &thickness);

	// compute volume of a washer
	outer_area = PI * pow(d2/2, 2);
	inner_area = PI * pow(d1/2, 2);
	rim_area = outer_area - inner_area;
	volume = rim_area * thickness;

	printf("Volume of washer = %.2f\n", volume);
	return 0;
}

