#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Use return-to-libc attack for this program.

int vul2(char *arg, char *buffer2)
{
  strcpy(buffer2, arg);
  return 0;
}

int vul1(char *argv[])
{
  char buffer[BUF6];
  vul2(argv[1], buffer);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf(stderr, "program6: argc != 2\n");
      exit(EXIT_FAILURE);
    }
  vul1(argv);
  return 0;
}
