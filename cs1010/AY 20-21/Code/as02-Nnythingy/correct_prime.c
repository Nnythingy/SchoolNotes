/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Prime
 *
 * Reads in an integer n from standard input and print 
 * the largest prime smaller or equal to n.
 *
 * @file: prime.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

bool is_prime(long n)
{
  if (n < 2) {
      return false;
  }
  for (long i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int main()
{
  long n = cs1010_read_long();
  for (long i = n; i >= 2; i -= 1) {
      if (is_prime(i)) {
        cs1010_println_long(i);
        return 0;
      }
  }
}