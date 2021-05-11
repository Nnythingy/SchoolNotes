/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: CountingSort
 *
 * Read in a series of numbers between 0 and 10000 
 * and sort them using counting sort.
 *
 * @file: countingsort.c
 * @author: Ng Jong Ray, Edward (Group BC1A)
 */
#include "cs1010.h"

void counting_sort(long list[], long total);
void sorting(long list[], long total);
long counting(long list[], long start, long total);

int main()
{
	long list_count = cs1010_read_long();
	long *list_input;
	list_input = cs1010_read_long_array(list_count);

	counting_sort(list_input, list_count);
	free(list_input);
}


void counting_sort(long list[], long total) {
	long end_flag = total;
	long element_value = 0;

	//sorting array
	while (end_flag > 1) {
		sorting(list, end_flag);
		end_flag -= 1;
	}

	//counting
	do {
		cs1010_print_long(list[element_value]);
		cs1010_print_string(" ");
		long results = counting(list, element_value, total);
		cs1010_println_long(results);
		element_value += results;
	} while (element_value < total); 

	//printing out sorted array
	for (long i = 0; i < total; i+=1) {
		cs1010_println_long(list[i]);
	}
}

//counting how many similar numbers in list
long counting(long list[], long start, long total) {
	long counter = 1;
	long flag = 0;

	for (long current_element = start; current_element < total-1; current_element+=1) {
		if (flag == 0 && list[current_element] == list[current_element+1]) {
			counter += 1;
		} else {
			flag = 1;
		}
	}
	return counter;
}

//sorting the list in order
void sorting(long list[], long total) {
	long swap = 0;

	//bubble sort
	for (long i = 0; i < (total-1); i += 1) {
		if (list[i] > list[i+1]) {
			swap = list[i];
			list[i] = list[i+1];
			list[i+1] = swap;
		}
	}
}
