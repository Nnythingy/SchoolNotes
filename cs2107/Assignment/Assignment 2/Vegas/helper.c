#include <stdio.h>
#include <stdlib.h>

int main() {
    srand(time(NULL));
    int num = rand() % 100 + 1;
    printf("%d", num);
    return 0;
}
