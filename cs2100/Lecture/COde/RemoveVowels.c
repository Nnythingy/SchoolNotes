// RemoveVowels.c 
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
	int i, len, count = 0;
	char str[101], newstr[101];

	printf("Enter a string (at most 100 characters): ");
	fgets(str, 101, stdin);
	len = strlen(str); // strlen(str) returns number of char in str
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
	len = strlen(str);

	for (i=0; i<len; i++) {
		switch (toupper(str[i])) {
			case 'A':
			case 'E':
			case 'I':
			case 'O':
			case 'U': break;
			default: newstr[count++] = str[i]; 
		}
	}
	newstr[count] = '\0';
	printf("Changed string: %s\n", newstr);

	return 0;	
}

