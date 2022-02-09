#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
char num[100];
int main() {
	gets(num);
	int mark = 0;
	int i, j;
	int cnt = 0;
	if (num[0] == '0') {
		if (strlen(num) == 1) {
			printf("0e0");
			return 0;
		} for (i=0; i<strlen(num); i++) {
			if (num[i] == '.') {
				continue;
			} if (num[i] != '0') {
				mark++;
			} if (mark == 0) {
				cnt++;
			} else if (mark == 1) {
				printf("%c", num[i]);
				if (num[i+1] != '\0') {
					printf(".");
				} mark++;
			} else if (mark > 1) {
				printf("%c", num[i]);
			}
		} printf("e-%d", cnt);
	} else {
		for (i=strlen(num)-1; i>=0; i--) {
			if (num[i] != '0') {
				break;
			} else if (num[i] == '0') {
				cnt++;
				num[i] = '\0';
				continue;
			}
		} for (i=0; i<strlen(num); i++) {
			if (num[i] == '.') {
				mark = 1;
				continue;
			} int temp = 0;
			for (j=i, i>0; j<strlen(num); j++) {
				if (num[j] >= '1' && num[j] <= '9') {
					temp = 1;
					break;
				}
			} if (temp == 1) {
				printf("%c", num[i]);
			}
			if (i == 0 && num[i+1] != '\0') {
				printf(".");
			} if (mark == 0) {
				cnt++;
			}
		} printf("e%d", cnt-1);
	}
	return 0;
}

