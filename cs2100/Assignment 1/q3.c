#include <stdio.h>

typedef struct {
    float num1;
    char ch;
    int num2;
} mystruct_t;

int main() {

    mystruct_t t1, t2[6];
    mystruct_t result = {0.0, ' ', 0};
    int i;

    printf("Structure component sizes:\n");
    printf("Size of t1.num1 = %lu bytes.\n", sizeof(t1.num1));
    printf("Size of t1.ch = %lu bytes.\n", sizeof(t1.ch));
    printf("Size of t1.num2 = %lu bytes.\n\n", sizeof(t1.num2));

    printf("Structure component addresses:\n");
    printf("Address of t1.num1 = %p.\n", &t1.num1);
    printf("Address of t1.ch = %p.\n", &t1.ch);
    printf("Address of t1.num2 = %p.\n\n", &t1.num2);

    printf("Array element addresses:\n");
    printf("Address of t2[0] = %p.\n", t2);
    printf("Address of t2[1] = %p.\n", &t2[1]);
    printf("Address of t2[2] = %p.\n", &t2[2]);

    for(i=0; i<6; i++)
        result.num2 = result.num2 + t2[i].num2;

    return 0;
}


