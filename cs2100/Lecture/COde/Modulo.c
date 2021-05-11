#include <stdio.h>

int main(void) {
	int a =  10 %  4;
	int b = -10 %  4;
	int c =  10 % -4;
	int d = -10 % -4;
	printf("%d %d %d %d\n", a, b, c, d);
	return 0;
}
