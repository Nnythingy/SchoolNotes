#include <stdio.h>

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int child_sigint_called = 0;
int child_child_sigint_called = 0;

void child_handle_sigint(int signum) {
  (void) signum;
  child_sigint_called = 1;
}

void child_child_handle_sigint(int signum) {
  (void) signum;
  child_child_sigint_called = 1;
}

int main() {
  signal(SIGINT, SIG_IGN);

  pid_t childpid = fork();
  if (childpid == 0) {
      signal(SIGINT, child_handle_sigint);
      int childchildpid = fork();
      if (childchildpid == 0) {
        signal(SIGINT, child_child_handle_sigint);
      }
  }
  
  setvbuf(stdout, NULL, _IONBF, 0);
  for (int i = 0; i < 120; ++i) {
    sleep(1);
    if (child_sigint_called == 1) {
        printf("\n\nchildren-child-SIGINT\n\n");
        return 0;
    }
    if (child_child_sigint_called == 1) {
        printf("\n\nchildren-child-child-SIGINT\n\n");
        return 0;
    }
    printf("\n\nchildren-%d\n\n", i);
  }
}
