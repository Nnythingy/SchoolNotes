/**
 * Read in a year and prints out if the input year is a leap year.
 * @file: leap.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"
#include <stdbool.h>

#include "cs1010.h"
#include <stdbool.h>

bool isLeap(long year) {
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int main() 
{
	long year = cs1010_read_long();

	cs1010_print_long(year);

	if(isLeap(year)) {
		cs1010_println_string(" is a leap year");
	} else {
		cs1010_println_string(" is not a leap year");
	}
}