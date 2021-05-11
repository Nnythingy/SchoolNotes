// WasherV2.c
// Modularised version of Washer.c
#include <stdio.h>
#include <math.h>
#define PI 3.14159

// double circle_area(double);

int main(void) {
	double d1, // inner diameter
	       d2, // outer diameter
	       thickness, rim_area, volume;      

	// read input data
	printf("Enter inner diameter, outer diameter, thickness: ");
	scanf("%lf %lf %lf", &d1, &d2, &thickness);

	// compute volume of a washer
	rim_area = circle_area(d2) - circle_area(d1);
	volume = rim_area * thickness;

	printf("Volume of washer = %.2f\n", volume);
	return 0;
}

// This function returns the area of a circle
double circle_area(double diameter) {
	return PI * pow(diameter/2, 2);
}

