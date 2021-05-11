// BreakInLoop.c
// To show how 'break' works in a loop.

#include <stdio.h>

int main(void) {
	int i, j;

	// without 'break'
	printf("Without 'break':\n");
	for (i=1; i<=5; i++) {
		printf("%d\n", i);
		printf("Ya\n");
	}

	// with 'break'
	printf("With 'break':\n");
	for (i=1; i<=5; i++) {
		printf("%d\n", i);
		if (i==3)
			break;
		printf("Ya\n");
	}

	// with 'break' in a nested loop
	printf("With 'break' in a nested loop:\n");
	for (i=1; i<=3; i++) {
		for (j=1; j<=5; j++) {
			printf("%d, %d\n", i, j);
			if (j==3)
				break;
			printf("Ya\n");
		}
	}

	return 0;
}

