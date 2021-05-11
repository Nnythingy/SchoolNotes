#include "cs1010.h"

long gcd(long a, long b) {
	if (b == 0) {
		return a;
	}

	return gcd(b, a % b);
}

int main() 
{
	long a = cs1010_read_long();
	long b = cs1010_read_long();

	cs1010_println_long(gcd(a, b));
}