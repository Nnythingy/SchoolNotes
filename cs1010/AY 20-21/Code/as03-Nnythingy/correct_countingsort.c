/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: CountingSort
 *
 * Read in a series of numbers between 0 and 10000 
 * and sort them using counting sort.
 *
 * @file: countingsort.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"

int main() {
  long size = cs1010_read_long();
  long max = 10000;
  long counter[10001] = {0};

  for (long i = 0; i < size; i += 1) {
    long num = cs1010_read_long();
    if (num >= 0 && num <= max) {
      counter[num] += 1;
    }
  }

  for (long i = 0; i <= max; i += 1) {
    if (counter[i] > 0) {
      cs1010_print_long(i);
      cs1010_print_string(" ");
      cs1010_println_long(counter[i]);
    }
  }

  for (long i = 0; i <= max; i += 1) {
    if (counter[i] > 0) {
      for (long j = 0; j < counter[i]; j += 1) {
        cs1010_println_long(i);
      }
    }
  }
}