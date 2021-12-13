#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char counter_file[12];
  int add_amount = 1;
  int counter_no = 0;

  if (argc >= 2) {
      add_amount = atoi(argv[1]);
      if (argc > 2) {
        counter_no = atoi(argv[2]);
      }
  }

  snprintf(counter_file, 12, "./counter%d", counter_no);

  FILE *fp;

  fp = fopen(counter_file, "r+");
  if (fp == NULL) {
      fp = fopen(counter_file, "w+");
  }

  int i;
  if (fscanf(fp, "%d", &i) == EOF) {
      i = 0;
  }

  fseek(fp, 0, SEEK_SET);
  fprintf(fp, "%d\n", i + add_amount);
  fclose(fp);

  return 0;
}
