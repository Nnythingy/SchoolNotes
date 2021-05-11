/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Pattern
 *
 * Read in two positive integers: an interval n (n >= 1) 
 * and the height of the triangle h.  Then draw a triangle
 * according to a given pattern.  
 *
 * @file: pattern.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

/**
 * Checks if n is prime.
 *
 * @pre n > 1
 * @param[in] n The number to check
 * @return true if n is prime, false if n is not.
 */
bool is_prime(long n)
{
  for (int i = 2; i <= sqrt(n); i += 1) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

/**
 * Checks if n is prime or 1
 *
 * @param[in] n The number to check
 * @return true if n is either prime or is 1, false if n is not.
 */
bool has_prime(long start, long run_size, long incr_size)
{
  long n = start;
  for (int i = 0; i < run_size; i += 1) {
    if (is_prime(n) || n == 1) {
      return true;
    }
    n += incr_size;
  }
  return false;
}

/**
 * Fill the standard outputs with `how_many` blanks.
 *
 * @param[in] how_many The number of blanks to write.
 */
void fill_blanks(long how_many) 
{
  for (long i = 0; i < how_many; i += 1) {
    cs1010_print_string(" ");
  }
}

/**
 * Print each row of the required patterns.
 *
 * @param[in] num_of_blanks The number of blanks to print on each 
 *                          side of the triangle
 * @param[in] num_of_fills The number of cells belonging to triangle.
 * @param[in] start The first number of each row.
 * @param[in] run_size The number of elements in each cell.
 * @param[in] incr_size How many numbers to skip (= row number + 1).
 */
void print_row(long num_of_blanks, long num_of_fills, long start, long run_size, long incr_size) 
{
  fill_blanks(num_of_blanks);
  for (long i = 0; i < num_of_fills; i += 1) {
    if (has_prime(start, run_size, incr_size)) {
      cs1010_print_string("#");
    } else {
      cs1010_print_string(" ");
    }
    start += 1;
  }
  fill_blanks(num_of_blanks);
  cs1010_println_string("");
}

int main()
{
  long run_size = cs1010_read_long();
  long height = cs1010_read_long();
  long num_of_blanks = height - 1;
  long num_of_fills = 1;
  long start = 1;
  long incr_size = 1;
  for (long row = 0; row < height; row += 1) {
    print_row(num_of_blanks, num_of_fills, start, run_size, incr_size);
    start += (incr_size * run_size);
    num_of_blanks -= 1;
    num_of_fills += 2;
    incr_size += 1;
  }
}