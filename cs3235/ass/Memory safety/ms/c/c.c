#include <stdio.h>
#include <stdlib.h>

void rop(FILE *f)
{
	char buf[!!BUF_SIZE!!];
	long i, fsize, read_size;

	puts("How many bytes do you want to read? (max: !!BUF_SIZE!!)");
	scanf("%ld", &i);
	
	if (i > !!BUF_SIZE!!) {
		puts("You can't trick me...");
		return;
	}

	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	read_size = (size_t) i < (size_t) fsize ? i : fsize; 
	fread(buf, 1, read_size, f);
	fclose(f);

	puts(buf);
}

int main(void)
{
	FILE *f = fopen("./exploit", "r");
	setbuf(f, 0);
	if (!f)
		puts("Error opening ./exploit");
	else
		rop(f);
	return 0;
}
