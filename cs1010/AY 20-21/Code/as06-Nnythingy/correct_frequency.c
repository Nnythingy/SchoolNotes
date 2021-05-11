/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: Permutation 2
 * 
 * Given 2 equal length string of small letter 'a' to 'z', this program checks if one is the permutation of the other
 *
 * @file: permutation2.c
 * @author: XXX (Group XXX)
 */

#include <stdbool.h>
#include <string.h>
#include "cs1010.h"

int main()
{
	//1st string
	char *s1;
	//2nd string
	char *s2;
	//length of string, which is the same for s1 and s2
	long l;
	//variable used for iteration
	long i;
	//count number of each character from 'a' to 'z'
	long c[26];
	//take inputs
	s1 = cs1010_read_word();
	s2 = cs1010_read_word();
	//initialize counter to 0
	for (i = 0; i < 26; i += 1) {
		c[i] = 0;
	}
	//fix length of the string
	l = (long)strlen(s1);
	//we increase counter by 1 for a character appearing in s1, but decreasing counter by 1 for appearing in s2
	for (i = 0; i < l; i += 1) {
		c[s1[i] - 'a'] += 1;
		c[s2[i] - 'a'] -= 1;
	}
	//find if counter of any character is not 0. If found, s1 is not permutation of s2
	for (i = 0; (i < 26 && c[i] == 0); i += 1) {
    }
	//output
	if (i < 26) {
		cs1010_println_string("NO");
	}
	else {
		cs1010_println_string("YES");
	}
	//free memory
	free(s1);
	free(s2);
}