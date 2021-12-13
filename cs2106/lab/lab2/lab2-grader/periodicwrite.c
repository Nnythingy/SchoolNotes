#include <stdio.h>

#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]) {
  setvbuf(stdout, NULL, _IONBF, 0);
  for (int i = 0; i < 120; ++i) {
    sleep(1);
    printf("\n\nperiodic-write-%d\n\n", i);
  }
}
