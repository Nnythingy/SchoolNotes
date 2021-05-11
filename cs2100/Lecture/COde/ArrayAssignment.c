// ArrayAssignment.c
#include <stdio.h>
#define N 10

int main(void) {
	int source[N] = { 10, 20 , 30 ,40, 50 };
	int dest[N];

	int i;
	for (i = 0; i < N; i++) {
		printf("%d ", source[i]);
	}
	printf("\n");

	dest = source;

	return 0;
}

