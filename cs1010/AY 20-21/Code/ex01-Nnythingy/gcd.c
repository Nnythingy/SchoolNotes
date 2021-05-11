/**
 * Read in two positive integers and find the greatest common divisors
 * among them, recursively.
 * @file: gcd.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"

long gcd(long num1, long num2){
	long remainder;
	if(num1 > num2){
		remainder = num1 % num2;
		if(remainder != 0){
			return gcd(num2, remainder);
		}
		return num2;
	}else if(num2 > num1){
		remainder = num2 % num1;
		if(remainder != 0){
			return gcd(num1, remainder);
		}
		return num1;
	}
	return num1;
}
int main() 
{
	long num1 = cs1010_read_long();
	long num2 = cs1010_read_long();
	cs1010_println_long(gcd(num1, num2));
}
