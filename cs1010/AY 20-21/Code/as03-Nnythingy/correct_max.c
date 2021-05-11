/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: Max
 *
 * Read in a sequence of numbers and recursively find
 * the maximum.
 *
 * @file: max.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"

long max(const long list[], long start, long end)
{
  // end > start
  if (start + 1 == end) {
    return list[start];
  }
  long mid = (start + end)/2;

  long left = max(list, start, mid);
  long right = max(list, mid, end);
  if (left > right) {
    return left;
  }
  return right;
}

int main()
{
  long num_of_elems = cs1010_read_long();
  long *list = cs1010_read_long_array(num_of_elems);

  if (num_of_elems == 1) {
    cs1010_println_long(list[0]);
  } else {
    cs1010_println_long(max(list, 0, num_of_elems));
  }
  free(list);
}