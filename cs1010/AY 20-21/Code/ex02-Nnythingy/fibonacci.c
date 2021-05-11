/**
 * CS1010 Semester 1 AY20/21
 * Exercise 2: Fibonacci
 *
 * Reads in an integer n from standard input and print the nth 
 * fibonacci number to the standard output.
 *
 * @file: fibonacci.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"

long fibonacci(long n) {
    if (n == 1 || n == 2) {
        return 1;
    }

    long first = 1;
    long second = 1;
    long third = 1;

    for (long i = 2; i != n; i += 1) {
        first = second;
        second = third;
        third = first + second;
    }

    return third;
}

int main()
{
    long n = cs1010_read_long();
    cs1010_println_long(fibonacci(n));
}
