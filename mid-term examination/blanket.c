#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
int func(int n) {
	if (n<=1) return 1;
	else return (2+n*func(n-1));
}
int main () {
	char *sp = "BUAA";
	printf("%s", sp);

	return 0;
}