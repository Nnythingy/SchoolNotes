// Filename: gdb_exploration.c
#include <stdio.h>
int f(int x, int y);
int g(int x, int y);
int main( ) {
    int a = 1, b = 2, c = 0;
    c = f(a, b);
    printf("Result = %d\n", c);
    return 0;
}
int f(int x, int y) {
    return (x+y) * g(x,y);
}
int g(int x, int y) {
    return x*y;
}
