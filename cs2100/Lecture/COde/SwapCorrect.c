// SwapCorrect.c
#include <stdio.h>

void swap(int *, int *);

int main(void) {
	int a = 2, b = 3;

	printf("In main, before: a=%d, b=%d\n", a, b);
	swap(&a, &b);
	printf("In main, after : a=%d, b=%d\n", a, b);
	return 0;
}

void swap(int *ptr1, int *ptr2) {
	int temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

