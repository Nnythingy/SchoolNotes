#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

void handle_sigusr(int signum) {
  (void) signum;
  _Exit(0);
}

int main() {
  signal(SIGUSR1, handle_sigusr);
  for (int i = 0; i < 10; ++i) {
    sleep(100000);
  }
}
