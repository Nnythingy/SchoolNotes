/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: Add
 *
 * @file: add.c
 * @author: XXX (Group YYY)
 */

#include <assert.h>
#include "cs1010.h"
#include <stdbool.h>

/**
 * Perform a single digit addition.  The digits are stored in
 * char form.
 *
 * @pre a and b can only be '0', '1', .. '9'
 * @param[in]             a The first operand of addition (in char)
 * @param[in]             b The second operand of addition (in char)
 * @param[in,out] has_carry Whether we should add a carry when adding 
 *                          a + b.  If a + b generates a carry, *has_carry
 *                          will be set to true, otherwise to false.
 *
 * @return The least significant digit of a+b (as char)
 */
char add_digit(char a, char b, bool *has_carry)
{
  long sum = (a - '0') + (b - '0');
  char result;
  if (*has_carry) {
    sum += 1;
  } 
  if (sum >= 10) {
    result = (char)(sum % 10) + '0';
    *has_carry = true;
  } else {
    result = (char)sum + '0';
    *has_carry = false;
  }
  return result;
}

int main()
{
  char *operand1 = cs1010_read_word();
  if (operand1 == NULL) {
    fprintf(stderr, "cannot read a word\n");
    return 1;
  }
  char *operand2 = cs1010_read_word();
  if (operand2 == NULL) {
    fprintf(stderr, "cannot read a word\n");
    return 1;
  }

  size_t len1 = strlen(operand1);
  size_t len2 = strlen(operand2);
  size_t max = (len1 > len2) ? len1 : len2;

  char *result;
  result = malloc((max + 2)*sizeof(char));
  if (result == NULL) {
      return 1;
  }
  result[max + 1] = '\0';

  // starting from the back, add digit by digit
  long i = (long)len1 - 1;
  long j = (long)len2 - 1;
  long k = (long)max;
  bool has_carry = false;
  while (i >= 0 && j >= 0) {
    assert(i >= 0);
    result[k] = add_digit(operand1[i], operand2[j], &has_carry);
    i -= 1;
    j -= 1;
    k -= 1;
  }

  // done with the shorter number.  Now handle the rest.
  char *rest;
  if (j >= 0) {
    rest = operand2;
  } else {
    rest = operand1;
    j = i;
  }
  
  while (j >= 0) {
    result[k] = add_digit(rest[j], '0', &has_carry);
    k -= 1;
    j -= 1;
  }

  if (has_carry) {
    result[k] = '1';
    cs1010_println_string(result);
  } else {
    cs1010_println_string(&result[1]);
  }
}
