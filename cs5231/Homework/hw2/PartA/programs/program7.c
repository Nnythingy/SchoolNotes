#include <stdio.h>
#include <stdlib.h>

void trickme(FILE *f)
{
	char buf[24];
	long i, fsize, read_size;

	puts("How many bytes do you want to read? (max: 24)");
	scanf("%ld", &i);
	
	if (i > 24) {
		puts("You can't trick me...");
		return;
	}

	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	read_size = i > fsize ? i : fsize; 
	fread(buf, 1, read_size, f);
	fclose(f);

	puts(buf);
}

int main(void)
{
	//sleep(10);
	FILE *f = fopen("/tmp/exploit7-file", "r");
	setbuf(f, 0);
	if (!f)
		puts("Error opening /tmp/exploit7-file");
	else
		trickme(f);
	return 0;
}
