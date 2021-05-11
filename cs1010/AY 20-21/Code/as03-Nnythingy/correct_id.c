/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: ID
 *
 * Read in a number and print out the check code 
 * according to NUS student ID algorithm.
 *
 * @file: id.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"

long sum_of_digits(long input)
{
    long curr = input;
    long sum = 0;
    while (curr != 0) {
        sum += curr % 10;
        curr = curr / 10;
    }
    return sum;
}


int main()
{
    char check_code[13] = { 'Y', 'X', 'W', 'U', 'R', 'N', 'M', 'L', 'J', 'H', 'E', 'A', 'B', };

    long id = cs1010_read_long();
    long sum = sum_of_digits(id);
    putchar(check_code[sum % 13]);
}