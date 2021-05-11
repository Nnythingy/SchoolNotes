// ContinueInLoop.c
// To show how 'continue' works in a loop.
#include <stdio.h>

int main(void) {
	int i, j;

	// without 'continue'
	printf("Without 'continue':\n");
	for (i=1; i<=5; i++) {
		printf("%d\n", i);
		printf("Ya\n");
	}

	// with 'continue'
	printf("With 'continue':\n");
	for (i=1; i<=5; i++) {
		printf("%d\n", i);
		if (i==3)
			continue;
		printf("Ya\n");
	}

	// with 'continue' in a nested loop
	printf ("With 'continue' in a nested loop:\n");
	for (i=1; i<=3; i++) {
		for (j=1; j<=5; j++) {
			printf("%d, %d\n", i, j);
			if (j==3)
				continue;
			printf("Ya\n");
		}
	}

	return 0;
}

