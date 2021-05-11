#include "cs1010.h"
/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Triangle
 *
 * Read in a positive integer h from standard input and 
 * print an equlateral triangle of height h.
 *
 * @file: triangle.c
 * @author: XXX (Group YYY)
 */

void draw_row(long row_num, long height) {
    // row k has (2k - 1) #
    // padded by h - k spaces
    for (long i = 0; i < height - row_num; i += 1) {
        cs1010_print_string(" ");
    }
    for (long i = 0; i < 2*row_num - 1; i += 1) {
        cs1010_print_string("#");
    }
    for (long i = 0; i < height - row_num; i += 1) {
        cs1010_print_string(" ");
    }
    cs1010_println_string("");
}

int main() {
    long height = cs1010_read_long();
    for (long row = 1; row <= height; row += 1) {
        draw_row(row, height);
    }
}