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
 * @param[in] degree_h The h-hop friendship information
 * @param[in] i A user
 * @param[in] j Another user 
 * @return FRIEND if i and j has a (h+1)-hop connection, STRANGER otherwise.
 */
char is_common_friend(long n, char **degree_one, char **degree_h, long i, long j) {
  for (int m = 0; m < n; m += 1) {
    if ((is_friend(degree_one, i, m) && is_friend(degree_h, m, j))) {
      return FRIEND;
    }
  }
  return STRANGER;
}

/**
 * Computers the h-hop friendship for the whole network.
 * @param[in] n          The number of users.
 * @param[in] degree_one The 1-hop friendship network
 * @param[out] degree_k   The h-hop friendship network
 */
void compute_degree_k_plus_one(long n, char **degree_one, char **degree_k, char **result) {
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; j <= i; j += 1) {
      if (is_friend(degree_k, i, j)) {
        result[i][j] = FRIEND;
      } else {
        result[i][j] = is_common_friend(n, degree_one, degree_k, i, j);;
      }
    }
  }
}

bool is_everyone_knows_everyone(long n, char **network) {
  for (int i = 0; i < n; i += 1) {
    for (int j = 0; j <= i; j += 1) {
      if (!is_friend(network, i, j)) {
        return false;
      }
    }
  }
  return true;
}

void print_social(long n, char **degree_one)
{
  for (int i = 0; i < n; i += 1) {
    cs1010_println_string(degree_one[i]);
  }
}

int main()
{
  long n = cs1010_read_long();
  long k = cs1010_read_long();
  char **degree_one;
  char **degree_k;
  char **result;

  degree_one = calloc((size_t)n, sizeof(char *));
  if (degree_one == NULL) {
      return 1;
  }
  degree_k = calloc((size_t)n, sizeof(char *));
  if (degree_k == NULL) {
      free(degree_one);
      return 1;
  }
  result = calloc((size_t)n, sizeof(char *));
  if (result == NULL) {
      free(degree_one);
      free(degree_k);
      return 1;
  }

  for (int i = 0; i < n; i ++) {
    degree_one[i] = cs1010_read_word();
    result[i] = calloc((size_t)i + 2, sizeof(char));
    degree_k[i] = calloc((size_t)i + 2, sizeof(char));
    for (long j = 0; j <= i; j++) {
      degree_k[i][j] = degree_one[i][j];
    }
  }

  for (int i = 1; i < k; i ++) {
    compute_degree_k_plus_one(n, degree_one, degree_k, result);
    swap(&degree_k, &result);
  }

  print_social(n, degree_k);

  for (int i = 0; i < n; i ++) {
    free(degree_one[i]);
    free(result[i]);
    free(degree_k[i]);
  }
  free(degree_one);
  free(degree_k);
  free(result);
}