/*
 * CS1010 Semester 1 AY20/21
 * Exercise 2: Rectangle
 * 
 * Reads in two integer numbers corresponding to the width and the 
 * height of a rectangle.   Draw the rectangle with character "*" 
 * to the standard output.
 *
 * @file: rectangle.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"

#define TOP_LEFT "╔"
#define TOP_RIGHT "╗"
#define BOTTOM_RIGHT "╝"
#define BOTTOM_LEFT "╚"
#define HORIZONTAL "═"
#define VERTICAL "║"

void drawTopLine(long width) {
    cs1010_print_string(TOP_LEFT);
    for(long i = 0; i < width - 2; i += 1) {
        cs1010_print_string(HORIZONTAL);
    }
    cs1010_println_string(TOP_RIGHT);
}

void drawBottomLine(long width) {
    cs1010_print_string(BOTTOM_LEFT);
    for(long i = 0; i < width - 2; i += 1) {
        cs1010_print_string(HORIZONTAL);
    }
    cs1010_println_string(BOTTOM_RIGHT);
}

void drawRectangle(long height, long width) {
    drawTopLine(width);
    for(long i = 0; i < height - 2; i += 1) {
        cs1010_print_string(VERTICAL);
        for(long j = 0; j < width - 2; j += 1) {
            cs1010_print_string(" ");
        }
        cs1010_println_string(VERTICAL);
    }
    drawBottomLine(width);
}

int main() {
    long width = cs1010_read_long();
    long height = cs1010_read_long();

    drawRectangle(height, width);
}
