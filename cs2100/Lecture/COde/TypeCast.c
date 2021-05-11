// TypeCast.c
#include <stdio.h>

int main(void) {    
	int   aa = 6;
	float ff = 15.8;

	float pp = (float) aa / 4;
	int   nn = (int) ff / aa;
	float qq = (float) (aa / 4);

	printf("pp = %f\n", pp);
	printf("nn = %d\n", nn);
	printf("qq = %f\n", qq);

	return 0;
}

