/**
 * CS1010 Semester 1 AY18/19
 * Assignment 7: Peak
 *
 * TODO(by student): Brief description of the purpose 
 * of this program.
 *
 * @file: peak.c
 * @author: XXX (Group XXX)
 */
#include "cs1010.h"
#include <assert.h>

/**
 * taken an array of integers, and start/end position
 * check if there's a peak based on problem desription
 * from start to end index in the array, inclusively
 * @param[in] l the array of integers
 * @param[in] start the staring index
 * @param[in] end the ending index
 * @return return the index of peak, or -1 if no peak exists
 */
long peak(long *l, long start, long end) {
	//no peak if less than 3 elements
	if (end < start + 2) {
		return -1;
	}
	long mid = (start + end) / 2;
	//return mid is mid element is larger than both ends, and hence it's a peak
	if (l[mid - 1] < l[mid] && l[mid + 1] < l[mid]) {
		return mid;
	}
	//case that mid point is flat at both side
	if (l[mid - 1] == l[mid] && l[mid + 1] == l[mid]) {
		long p = peak(l, start, mid);
		if (p > -1) {
			//return peak value if found in the left side
			return p;
		}
		//return peak value found in the right side including -1
		return peak(l, mid, end);
	}
	//case that peak is in the 2nd half of the list
	if (l[mid - 1] <= l[mid] && l[mid + 1] >= l[mid]) {
		return peak(l, mid, end);
	}
	//case that peak is in 1st half of the list
	assert(l[mid - 1] >= l[mid] && l[mid + 1] <= l[mid]);
	return peak(l, start, mid);
}

int main()
{
	long *l;
	long n;
	n = cs1010_read_long();
	l = cs1010_read_long_array(n);
	n = peak(l, 0, n - 1);
	if (n > -1) {
		cs1010_println_long(n);
	}
	else {
		cs1010_println_string("no peak");
	}
	free(l);
}