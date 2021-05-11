#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "usage: %s <n>", argv[0]);
    return 1;
  }
  srandom(times(0));

  char *end;
  long n = strtol(argv[1], &end, 10);

  int seq[n];
  for (int i = 0; i < n; i++) {
    seq[i] = i+1;
  }

  for (int i = 0; i < n; i++) {
    int pos1 = random() % n;
    int pos2 = random() % n;
    int temp;
    temp = seq[pos1];
    seq[pos1] = seq[pos2];
    seq[pos2] = temp;
  }

  for (int i = 0; i < n; i++) {
    printf("%d ", seq[i]);
  }
}