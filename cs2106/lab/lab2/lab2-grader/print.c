#include <stdio.h>

#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("\n\nprint-emptynoarg\n\n");
    return 0;
  }
  setvbuf(stdout, NULL, _IONBF, 0);
  printf("\n\nprint-%s\n\n", argv[1]);
  return 0;
}
