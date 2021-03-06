/**
 * CS1010 Semester 1 AY20/21
 * Assignment 1: Suffix
 *
 * Read in a number and prints out the number with the appropriate suffix.
 *
 * @file: suffix.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"

void print_suffix(long number)
{
    cs1010_print_long(number);

    long last_digit = number % 10;
    long penultimate_digit = (number / 10) % 10;

    if (last_digit == 1 && penultimate_digit != 1) {
        cs1010_println_string("st");
    } else if (last_digit == 2 && penultimate_digit != 1) {
        cs1010_println_string("nd");
    } else if (last_digit == 3 && penultimate_digit != 1) {
        cs1010_println_string("rd");
    } else {
        cs1010_println_string("th");
    }
}

int main() 
{
    long number = cs1010_read_long();
    print_suffix(number);
}