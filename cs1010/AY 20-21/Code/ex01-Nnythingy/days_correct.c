#include "cs1010.h"


long calDays(long currMonth) {
	long daysAtMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	long days = 0;
	for(long i = 1; i < currMonth; i += 1) {
		days += daysAtMonth[i - 1];
	}	

	return days;
}

int main() {
	long currMonth = cs1010_read_long();
	long currDays = cs1010_read_long();

	cs1010_println_long(calDays(currMonth) + currDays);
}