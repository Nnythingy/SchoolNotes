/*
 * CS1010 Semester 1 AY20/21
 * Exercise 2: Binary
 *
 * Reads in a number containing only digits 0 and 1, interpret 
 * it as a binary number, and output the corresponding decimal
 * number.
 *
 * @file: binary.c
 * @author: XXX (Group YYY)
 */
#include "cs1010.h"
#include <math.h>

long converter(long binary);

int main()
{
    long input = cs1010_read_long();
    cs1010_println_long(converter(input));
}

long converter(long binary){
    long total = 0;
    long i = 0;
    while (binary != 0){
        if (binary%10 == 1){
            total += pow(2, i);
            binary /= 10;
            i += 1;
        }else{
            binary /= 10;
            i += 1;
        }
    }
    return total;
}
//correct answer

/*#include "cs1010.h"
#include <math.h>

long convertBinary(long binary) {
    long currPower = 0;
    long decimal = 0;

    while (binary != 0) {
        long LSB = binary % 10;
        decimal += LSB * pow(2, currPower);

        binary /= 10;
        currPower += 1;
    }

    return decimal;
}

int main() {
    long binary = cs1010_read_long();
    cs1010_println_long(convertBinary(binary));
}
*/
