#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct wid {
  double x[7];
  int count;
  int delivered;
};

#define MW 884

int vul1(char *input, int count)
{
  struct wid buffer[MW];

  if (count < MW) 
    memcpy(buffer, input, count * sizeof(struct wid));

  return 0;
}

int main(int argc, char *argv[])
{
  int count;
  char *input;

  if (argc != 2)
    {
      fprintf(stderr, "program3: argc != 2\n");
      exit(EXIT_FAILURE);
    }

  /*
   * format of argv[1] is as follows:
   *
   * - a count, encoded as a decimal number in ASCII
   * - a comma (",")
   * - the remainder of the data, treated as an array
   *   of struct wid
   */

  count = (int)strtoul(argv[1], &input, 10);
  if (*input != ',')
    {
      fprintf(stderr, "program3: argument format is [count],[data]\n");
      exit(EXIT_FAILURE);
    }
  input++;                         /* advance one byte, past the comma */
  vul1(input, count);

  return 0;
}
