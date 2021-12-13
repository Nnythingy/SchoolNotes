#include <stdlib.h>

#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    sleep(1);
    return 0;
  } else {
    sleep(atoi(argv[1]));
    return 0;
  }
}
