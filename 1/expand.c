#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
char string[100];
int main()
{
	gets(string);
	int i, j;
	for (i=0; i<strlen(string); i++) {
		if (string[i] != '-') {
			printf("%c", string[i]);
		} else {
			if ((string[i-1] >= 'a' && string[i-1] <= 'z' && string[i+1] >= 'a' && string[i+1] <= 'z' && string[i-1] < string[i+1]) ||
			(string[i-1] >= 'A' && string[i-1] <= 'Z' && string[i+1] >= 'A' && string[i+1] <= 'Z' && string[i-1] < string[i+1]) ||
			(string[i-1] >= '0' && string[i-1] <= '9' && string[i+1] >= '0' && string[i+1] <= '9' && string[i-1] < string[i+1])) {
			for(j=string[i-1]+1; j<=string[i+1]-1; j++) {
				printf("%c", j);
				
				}
			} else {
				printf("-");
			}
		}
	}
	return 0;
}

