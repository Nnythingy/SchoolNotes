#include<stdio.h>
#include<string.h>

static int i;

static void generate_calendar(){
  int calendar[!!BUF_SIZE!!];
  int days;
  int start, step;

  memset(calendar, 0, sizeof(calendar));
  puts("Enter number of days: ");
  scanf("%d", &days);
  if(days > !!BUF_SIZE!!)
    days = !!BUF_SIZE!!;
  puts("Enter starting date: ");
  scanf("%d", &start);
  puts("Enter interval: ");
  scanf("%d", &step);

  for(i = start; i < days; i += step){
    printf("Your planned event for day %d: ", i);
    scanf("%d", calendar + i);
  }

  printf("Your calendar:");
  for(i = 0; i < days; i ++)
    printf(" %d", calendar[i]);
  printf("\n");
}

int main(){
  generate_calendar();

  return 0;
}


