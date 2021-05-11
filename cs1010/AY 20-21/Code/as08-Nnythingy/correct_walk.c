#include "cs1010.h"
#include <string.h>

long ne(long m, long n) {
    long solve[m+1][n+1]; // cheating with VLA
    for (long i = 0; i <= m; i += 1) {
        solve[i][0] = 1;
    }
    for (long i = 0; i <= n; i += 1) {
        solve[0][i] = 1;
    }
    for (long i = 1; i <= m; i += 1) {
        for (long j = 1; j <= n; j += 1) {
            solve[i][j] = solve[i-1][j] + solve[i][j-1];
        }
    }
    return solve[m][n];
}

int main() {
  long m, n;
  m = cs1010_read_long();
  n = cs1010_read_long();
  cs1010_println_long(ne(m, n));
}