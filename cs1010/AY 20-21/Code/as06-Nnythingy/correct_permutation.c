/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: Permutation 3
 * 
 * Given two strings of lowercase letters 'a' to 'z', with first string 
 * no longer than the second. This program checks if the 1st string is 
 * a permutation of a substring of 2nd one.
 *
 * @file: permutation3.c
 * @author: XXX (Group XXX)
 */
#include "cs1010.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * Compares if two strings are permutation of each other, by
 * checking their frequency array.
 *
 * @param[in] freq1 The frequency array for the first string.
 * @param[in] freq2 The frequency array for the second string.
 *
 * @return true if the two strings contains the same frequency 
 *         array, false otherwise.
 */
bool is_permutation(const long freq1[26], const long freq2[26]) {
  for (long i = 0; i < 26; i += 1) {
    if (freq1[i] != freq2[i]) {
      return false;
    }
  }
  return true;
}

/**
 * Update the frequency table for a new subtring of length k of s2, 
 * starting from position start.
 *
 * @pre start >= 1 && start <= n - k
 * @param[in,out] freq The frequency table to update
 * @param[in] s2 The string
 * @param[in] start The beginning position of the substring
 * @param[in] k The length of the substring.
 */
void update_frequency(long freq2[26], const char *s2, int start, int k) {
  freq2[s2[start-1]-'a'] -= 1;
  freq2[s2[start+k-1]-'a'] += 1;
}

/**
 * Initialize a frequency array counting how many times each letter
 * appears in a string.
 *
 * @param[in] len The length of the string.
 * @param[in] s The string 
 * @param[out] freq The frequency array.
 */
void build_frequency_array(long len, const char s[len], long freq[26]) {
  for (long i = 0; i < 26; i += 1) {
    freq[i] = 0;
  }
  for (long i = 0; i < len; i += 1) {
    freq[s[i]-'a'] += 1;
  }
}

/**
 * Find if s1 is a permutation of a substring of s2.
 *
 * @param[in] s1 The (shorter) string
 * @param[in] s2 The string to search for a permutation of s1 in.
 *
 * @return true if s1 is a permutation of a substring of s2.
 */
bool find_permutation(char *s1, char *s2) {
  long k = strlen(s1);
  long n = strlen(s2);

  long freq1[26];
  long freq2[26];

  build_frequency_array(k, s1, freq1);
  build_frequency_array(k, s2, freq2);

  if (is_permutation(freq1, freq2)) {
    return true;
  }

  for (long start = 1; start <= n - k; start += 1) {
    update_frequency(freq2, s2, start, k);
    if (is_permutation(freq1, freq2)) {
      return true;
    }
  }
  return false;
}

int main()
{
  char *s1 = cs1010_read_word();
  char *s2 = cs1010_read_word();

  bool found = find_permutation(s1, s2);

	if (found) {
		cs1010_println_string("YES");
	} else {
		cs1010_println_string("NO");
	}
	
	free(s1);
	free(s2);
}