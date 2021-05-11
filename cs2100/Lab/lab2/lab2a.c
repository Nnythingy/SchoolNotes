#include <stdio.h>

void display(int);

int main() {
    int ageArray[] = { 2, 15, 4 };
    display(ageArray[0]);
    //printf("Size of the array is %d\n", ageArray[2]);
    //printf("Size of the array is %ld\n", (sizeof(ageArray)/sizeof(ageArray[0])));
    printf("Stored value is: %d\n, address value is %p\n", ageArray[0], ageArray);
    printf("Stored value is: %d\n, address value is %p\n", *(ageArray+2), &ageArray[0]);
    return 0;
}

void display(int age) {
    printf("%d\n", age);
}
