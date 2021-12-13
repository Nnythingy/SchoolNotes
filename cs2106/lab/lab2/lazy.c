#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

void handle_sigusr(int signum) {
  (void) signum;
  sleep(5);
  _Exit(0);
}

int main() {
  signal(SIGTERM, handle_sigusr);
  for (int i = 0; i < 10; ++i) {
    sleep(100000);
  }
}
