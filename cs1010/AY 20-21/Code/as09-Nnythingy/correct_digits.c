#include "cs1010.h"
#include <assert.h>
#include <limits.h>

#define NCOLS 28
#define NROWS 28
#define WHITE '.'
#define BLACK '#'
#define K 5

typedef struct {
  char *input[NROWS];
  long label;
} digit;

typedef struct {
  digit sample;
  long distance;
} neighbor;

void digit_read(digit *sample)
{
  sample->label = cs1010_read_long();
  for (long i = 0; i < NROWS; i += 1) {
    sample->input[i] = cs1010_read_word();
  }
}

void digit_print(digit *sample)
{
  for (long i = 0; i < NROWS; i += 1) {
    cs1010_println_string(sample->input[i]);
  }
}


long find_distance(digit a, digit b, long limit) {
  long d = 0;
  for (long i = 0; i < NROWS; i += 1) {
    for (long j = 0; j < NCOLS; j += 1) {
      if ((a.input[i][j] == BLACK && b.input[i][j] == WHITE) ||
          (a.input[i][j] == WHITE && b.input[i][j] == BLACK)) {
        d += 1;
        if (d > limit) {
          return d;
        }
      }
    }
  }
  if (d == 0) {
      digit_print(&a);
      digit_print(&b);
  }
  return d;
}

long most_common_digit(const neighbor nearest[K])
{
  long freq[10];
  long dist[10];
  for (long i = 0; i < 10; i += 1) {
      freq[i] = 0;
      dist[i] = LONG_MAX;
  }

  for (long i = 0; i < K; i += 1) {
    long digit = nearest[i].sample.label;
    freq[digit] += 1;
    if (nearest[i].distance < dist[digit]) {
        dist[digit] = nearest[i].distance;
    }
  }
  long max_so_far = freq[0];
  long max_digit = 0;
  for (long i = 1; i < 10; i += 1) {
    if ((freq[i] > max_so_far) || (freq[i] != 0 && freq[i] == max_so_far && dist[i] < dist[max_digit])) {
      max_so_far = freq[i];
      max_digit = i;
    }
  }
  return max_digit;
}

void insert(digit sample, long distance, neighbor nearest[]) {
  long curr = K-1;
  if (distance > nearest[K-1].distance) {
    return;
  }
  if (distance == nearest[K-1].distance && sample.label > nearest[K-1].sample.label) {
    return;
  }
  // assert(distance < nearest[K-1].distance || (distance == nearest[K-1].distance && sample.label < nearest[K-1].label));
  do {
    nearest[curr] = nearest[curr-1];
    curr = curr - 1;
  } while (curr >= 0 && (nearest[curr].distance > distance || (nearest[curr].distance == distance && nearest[curr].sample.label > sample.label)));
  // { nearest[curr].distance <= sample.distance }
  nearest[curr+1].sample = sample;
  nearest[curr+1].distance = distance;
}

long recognize(digit test, long num_of_samples, digit samples[]) 
{
  neighbor nearest[K];

  for (long i = 0; i < K; i += 1) {
    nearest[i].distance = LONG_MAX;
  }

  for (long i = 0; i < num_of_samples; i += 1) {
    long d = find_distance(test, samples[i], nearest[K-1].distance);
    insert(samples[i], d, nearest);
  }

  /*
  for (long i = 0; i < K; i += 1) {
    printf("-- %ld %ld\n", nearest[i].sample.label, nearest[i].distance);
  }
  */

  return most_common_digit(nearest);
}

int main()
{
  long num_of_samples = cs1010_read_long();
  digit *samples = calloc((size_t)num_of_samples, sizeof(digit));
  for (long i = 0; i < num_of_samples; i += 1) {
    digit_read(&samples[i]);
  }

  long num_of_tests = cs1010_read_long();
  digit test;
  int error = 0;
  for (long i = 0; i < num_of_tests; i += 1) {
    digit_read(&test);
    long answer = recognize(test, num_of_samples, samples);
    if (answer != test.label) {
      error += 1;
    }
    cs1010_print_long(test.label);
    cs1010_print_string(" ");
    cs1010_println_long(answer);
  }
  cs1010_println_double((num_of_tests - error)*100.0/num_of_tests);
  free(samples);
}

