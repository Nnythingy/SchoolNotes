#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_str(char *buffer2, int buffer2_l, char *input)
{
  int i, length;

  length = strlen(input);
  if (length > buffer2_l)
    length = buffer2_l;

  for (i = 0; i <= length; i++)
    buffer2[i] = input[i];
}

void vul2(char *arg)
{
  char buffer[BUF2];

  copy_str(buffer, sizeof buffer, arg);
}

void vul1(char *argv[])
{
  vul2(argv[1]);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf(stderr, "program2: argc != 2\n");
      exit(EXIT_FAILURE);
    }
  vul1(argv);
  return 0;
}
