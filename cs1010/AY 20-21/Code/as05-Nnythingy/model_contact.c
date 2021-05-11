#include "cs1010.h"
#include <stdbool.h>
#include <stdlib.h>

#define FRIEND '1'
#define STRANGER '0'

void swap(char ***a, char ***b) {
  char **temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * Checks if i is connected to j in the given social network.
 * @param[in] network The social network
 * @param[in] i A user
 * @param[in] j Another user
 * @return true if i and j are connected in network, false otherwise.
 */
bool is_friend(char **network, long i, long j) {
  if (i >= j) {
    return network[i][j] == FRIEND;
  }
  return network[j][i] == FRIEND;
}

/**
 * Checks if i and j has a common friend
 * @param[in] n The number of users
 * @param[in] degree_one The 1-hop friendship information
 * @param[in] i A user
 * @param[in] j Another user 
 * @return FRIEND if i and j has a (h+1)-hop connection, STRANGER otherwise.
 */
long find_common_friend(long n, char **degree_one, long i, long j) {
  for (long m = 0; m < n; m += 1) {
    if ((is_friend(degree_one, i, m) && is_friend(degree_one, m, j))) {
      return m;
    }
  }
  return -1;
}

int main()
{
  long n = cs1010_read_long();
  char **degree_one;

  degree_one = calloc((size_t)n, sizeof(char *));
  if (degree_one == NULL) {
      return 1;
  }

  for (int i = 0; i < n; i ++) {
    degree_one[i] = cs1010_read_word();
  }

  long j = cs1010_read_long();
  long k = cs1010_read_long();
  if (is_friend(degree_one, j, k)) {
      cs1010_println_string("direct contact");
  } else {
      long m = find_common_friend(n, degree_one, j, k);
      if (m != -1) {
          cs1010_print_string("contact through ");
          cs1010_println_long(m);
      } else {
          cs1010_println_string("no contact");
      }
  }

  for (long i = 0; i < n; i ++) {
    free(degree_one[i]);
  }
  free(degree_one);
}