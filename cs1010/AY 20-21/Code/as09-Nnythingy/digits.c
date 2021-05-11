/**
 * CS1010 Semester 1 AY20/21
 * Assignment 9: Digits
 *
 * TODO(by student): Brief description of the purpose 
 * of this program.
 *
 * @file: digits.c
 * @author:
 */

#include "cs1010.h"
#include <math.h>

#define NCOLS 28
#define NROWS 28
#define WHITE '.'
#define BLACK '#'
#define K 5

typedef struct {
	char **image;
	long num;
} digit;

typedef struct {
	char **image;
	long num;
} neighbor;

void readImage(digit *number);
long comparing(digit *test, long input, digit *training);
long counting(long list[5][2]);
long max(long list[]);
long maxIndex(long list[5][2]);

int main()
{
	long input = cs1010_read_long();
	digit *training = malloc((size_t)input*sizeof(digit));
	if (training == NULL) {
		cs1010_println_string("exit");
		free(training);
		return 1;
	}

	//reading training data
	for (long i = 0; i < input; i += 1) {
		readImage(&training[i]);
	}

	//testing data
	long testingNum = cs1010_read_long();
	long correctTest = 0;
	for(long i = 0; i < testingNum; i += 1) {
		digit testInput = {
			.num = 0,
			.image = NULL,
		};

		readImage(&testInput);
		long correctAns = comparing(&testInput, input, training);
		if (testInput.num == correctAns) {
			correctTest += 1;
		}
		cs1010_print_long(testInput.num);
		cs1010_print_string(" ");
		cs1010_print_long(correctAns);
		cs1010_println_string("");
		for (long j = 0; j < NROWS; j += 1) {
			free(testInput.image[j]);
		}
		free(testInput.image);
	}

	cs1010_print_double(((double)correctTest/(double)testingNum)*(double)100);

	//free
	free(training);
}

void readImage(digit *number) {
	number->num = cs1010_read_long();
	number->image = malloc((size_t)NROWS*sizeof(char *));
	if (number->image == NULL) {
		cs1010_println_string("exit");
		free(number->image);
		return;
	}
	for (long i = 0; i < NROWS; i += 1) {
		number->image[i] = cs1010_read_word();
	}
}

long comparing(digit *test, long input, digit *training) {
	long difference = 0;
	long neighbourData[K][2] = {{0}};
	long tmp = 0;

	for (long i = 0; i < input; i += 1) {
		for (long j = 0; j < NROWS; j += 1) {
			for (long k = 0; k < NCOLS; k += 1) {
				//checking each cell
				if (test->image[j][k] != training[i].image[j][k]) {
					difference += 1;
				}
			}
		}
		if (i < K) {
			neighbourData[i][0] = training[i].num;
			neighbourData[i][1] = difference;
		} else {
			for (long j = 0; j < K; j += 1) {
				if (difference < neighbourData[j][1]) {
					tmp = maxIndex(neighbourData);
					neighbourData[tmp][0] = training[i].num;
					neighbourData[tmp][1] = difference;
				}
			}
		}
	}
	//returns the what the correct number should be
	return (counting(neighbourData));
}

long counting(long list[5][2]) {
	long array[10] = {0};

	for (long i = 0; i < K; i += 1) {
		array[list[i][0]] += 1;
	}
	return (max(array));
}

long max(long list[]) {
	long max_so_far = list[0];
	long max_index = 0;
	for (long i = 1; i < K; i += 1) {
		if (list[i] > max_so_far) {
			max_so_far = list[i];
			max_index = i;
		}
	}
	return max_index;
}

long maxIndex(long list[5][2]) {
	long max_so_far = list[0][1];
	long max_index = 0;
	for (long i = 1; i < K; i += 1) {
		if (list[i][1] > max_so_far) {
			max_so_far = list[i][1];
			max_index = i;
		}
	}
	return max_index;
}
