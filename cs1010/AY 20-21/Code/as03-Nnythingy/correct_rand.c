#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

int main(int argc, char *argv[])
{
  if (argc != 4) {
    fprintf(stderr, "usage: %s <n> <bottom> <top>", argv[0]);
    return 1;
  }
  srandom(times(0));

  char *end;
  long n = strtol(argv[1], &end, 10);
  long b = strtol(argv[2], &end, 10);
  long t = strtol(argv[3], &end, 10);

  for (int i = 0; i < n; i++) {
    double d = (1.0*random()/RAND_MAX)*(t - b) + b;
    printf("%lf\n", d);
  }
}