/**
 * CS1010 Semester 1 AY20/21
 * Exercise 0: Echo
 *
 * Read in an integer and print it on the screen.
 *
 * @file: echo.c
 * @author: XXX (Group YYY)
 */

#include "cs1010.h"

long echo(){
	long repeat = cs1010_read_long();
	return repeat;
}

int main()
{
	long printed = echo();
	cs1010_print_long(printed);
	return 0;
}
