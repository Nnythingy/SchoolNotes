#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1024

int main(int argc, char *argv[]) {
  if (argc > 1) {
    fprintf(stdout, "%s", argv[1]);
    fprintf(stderr, "%s", argv[1]);
    return 0;
  } else {
    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, stdin) != NULL) {
        fprintf(stdout, "%s", line);
        fprintf(stderr, "%s", line);
    }
    return 0;
  }
}
