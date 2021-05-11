/**
 * CS1010 Semester 1 AY20/21
 * Exercise 0: Divide
 *
 * Read in two integers and print the result of dividing the first 
 * by the second to the standard output.
 *
 * @file: divide.c
 * @author: XXX (Group YYY)
 */

#include "cs1010.h"

double divide(long num1, long num2);

int main()
{ 
	long num1 = cs1010_read_long();
	long num2 = cs1010_read_long();
	double answer = divide(num1, num2);
	cs1010_print_double(answer);
	return 0;
}

double divide(long num1, long num2){
	double answer = num1/(double)num2;
	return answer;
}

