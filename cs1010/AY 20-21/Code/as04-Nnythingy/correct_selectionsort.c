/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: SelectionSort
 *
 * @file: selectionsort.c
 * @author: XXX (Group YYY)
 */

#include "cs1010.h"

long max(long length, const long list[])
{
  long max_so_far = list[0];
  long max_index = 0;
  for (long i = 1; i != length; i += 1) {
    if (list[i] > max_so_far) {
      max_so_far = list[i];
      max_index = i;
    }
  }
  return max_index;
}

void print(long length, const long list[]) 
{
  for (long i = 0; i < length; i += 1) {
    cs1010_print_long(list[i]);
    cs1010_print_string(" ");
  }
  cs1010_println_string("");
}

void selection_sort(long length, long list[])
{
  long last = length;
  for (long i = 1; i <= length - 1; i += 1) {
    long curr_pos = last - 1;
    long max_pos = max(last, list);
    if (max_pos != curr_pos) {
      long temp = list[max_pos];
      list[max_pos] = list[curr_pos];
      list[curr_pos] = temp;
    }
    print(length, list);
    last -= 1;
  }
  
}


int main() 
{
  long n = cs1010_read_long();
  long *list = cs1010_read_long_array(n);
  selection_sort(n, list);
}