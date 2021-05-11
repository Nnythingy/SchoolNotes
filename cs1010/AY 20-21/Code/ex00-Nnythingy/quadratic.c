/**
 * CS1010 Semester 1 AY20/21
 * Exercise 0: Quadratic
 *
 * Read in three doubles, a, b, and c, that represents the quadratic
 * equaltion a*x*x + b*x + c = 0 and print the two roots of this 
 * equation.
 *
 * @file: quadratic.c
 * @author: XXX (Group YYY)
 */

#include "cs1010.h"
#include <math.h>

double divide(double num1, double num2);
double square(double num1);
void quadratic(long a, long b, long c);

int main()
{
	long a = cs1010_read_long();
	long b = cs1010_read_long();
	long c = cs1010_read_long();
	quadratic(a, b ,c);
	return 0;
}

double divide(double num1, double num2){
	double answer = num1 / num2;
	return answer;
}

double square(double num1){
	double answer = num1 * num1;
	return answer;
}

void quadratic(long aaa, long bbb, long ccc){
	double b_sqr = square(bbb);
	long four_ac = 4 * aaa * ccc;
	double sqr_root = sqrt(b_sqr - four_ac);
	double root1_top_half = (-bbb + sqr_root);
	double root2_top_half = (-bbb - sqr_root);
	double root1 = divide(root1_top_half, 2 * aaa);
	double root2 = divide(root2_top_half, 2 * aaa);
	cs1010_println_double(root1);
	cs1010_print_double(root2);
}
