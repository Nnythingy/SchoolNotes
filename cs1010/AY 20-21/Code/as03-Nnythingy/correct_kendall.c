/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: Kendall
 *
 * Read in a sequence of numbers and find its kendall tau 
 * distance.
 *
 * @file: kendall.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"

long count_inversion(long start, long len, const long rank[len])
{
  long count = 0;
  for (long j = start + 1; j < len; j += 1) {
    if (rank[start] > rank[j]) {
      count ++;
    }
  }
  return count;
}

double kendall_tau(long len, long rank[len])
{
  long count = 0;
  for (long i = 0; i < len - 1; i += 1) {
    count += count_inversion(i, len, rank);
  }

  return 2.0*count/(len*(len - 1));
}

int main()
{
  long len = cs1010_read_long();
  long* rank = cs1010_read_long_array(len);

  double distance = kendall_tau(len, rank);

  cs1010_println_double(distance);
  free(rank);
}