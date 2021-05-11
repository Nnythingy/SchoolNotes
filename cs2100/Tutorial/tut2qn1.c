#include <stdio.h>

typedef unsigned char byte_t;
void printByte(byte_t);
void swap(int*, int*);

int main(void) {
    byte_t a, b;
    int c = 5;
    int d = 6;
    a = 5;
    b = 22;
    printf("a = "); printByte(a); printf("\n");
    printf("b = "); printByte(b); printf("\n");
    printf("a|b = "); printByte(a|b); printf("\n");

    printf("trying to swap\n");
    swap(&c, &d);
    printf("c = %d. d = %d \n", c, d);
    return 0;
}

void printByte(byte_t x) {
    printf("%c%c%c%c%c%c%c%c",
            (x & 0x80 ? '1': '0'),
            (x & 0x40 ? '1': '0'),
            (x & 0x20 ? '1': '0'),
            (x & 0x10 ? '1': '0'),
            (x & 0x08 ? '1': '0'),
            (x & 0x04 ? '1': '0'),
            (x & 0x02 ? '1': '0'),
            (x & 0x01 ? '1': '0'));
}

void swap(int* a, int* b) {
    *a = *a^*b;
    *b = *a^*b;
    *a = *a^*b;
}
