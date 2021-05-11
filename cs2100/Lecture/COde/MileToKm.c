// MileToKm.c
// Converts distance in miles to kilometers.
#include <stdio.h>
#define KMS_PER_MILE 1.609  

int main(void) {
	float miles,   // input - distance in miles. 
		  kms;     // output - distance in kilometers

	/* Get the distance in miles */
	printf("Enter distance in miles: ");
	scanf("%f", &miles);

	// Convert the distance to kilometres
	kms = KMS_PER_MILE * miles;

	// Display the distance in kilometres
	printf("That equals %9.2f km.\n", kms);

	return 0;
}

