#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int jackpot;

static void get_flag(){
	FILE* fin;
	unsigned long long flag;
	fin = fopen("./flag.txt", "r");
	fscanf(fin, "%llu", &flag);
	fclose(fin);

	printf("Your flag is %llu\n", flag);
}

void fmt_str(void)
{
	char buf[!!BUF_SIZE!!];
	puts("Give me a string to print");
	read(0, buf, !!BUF_SIZE!!);
	printf(buf);

	printf("jackpot @ %p = %d [0x%08x]\n", &jackpot, jackpot, jackpot);
	if (jackpot == !!RAND_INT!!){
		puts("You won!");
		get_flag();
	} else
		puts("You lost :(");

}

int main(void)
{
	srand(time(0));
	setbuf(stdout, 0);

	jackpot = rand();
	fmt_str();	
	return 0;
}
