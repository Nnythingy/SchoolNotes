#include<stdio.h>

int main(){
	FILE* fin = fopen("./flag.txt", "r");
	unsigned long long flag;
	fscanf(fin, "%llu", &flag);
	printf("Your flag is %llu\n", flag);
	fclose(fin);
	return 0;
}
