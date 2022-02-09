#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
char a[100];
char b[100];
int rec_max[100];
int rec_min[100];
int res[100];
int main()
{
	gets(a);
	gets(b);
	int sign; //1代表正数 -1代表负数 0代表0 
	int i;
	int flag_1 = 0, flag_2 = 0;
	i = 0; 
	while(a[i] =='0') {
		flag_1++;
		i++;
	} i = 0; 
	while(b[i] == '0') {
		flag_2++;
		i++;
	}
	if (strlen(a+flag_1) > strlen(b+flag_2) || (strlen(a+flag_1) == strlen(b+flag_2) && strcmp(a+flag_1, b+flag_2) > 0)) {
		sign = 1;
	} else if (strlen(a+flag_1) < strlen(b+flag_2) || (strlen(a+flag_1) == strlen(b+flag_2) && strcmp(a+flag_1, b+flag_2) < 0)) {
		sign = -1;
	} else {
		sign = 0;
	} if (sign == 0) {
		printf("0");
		return 0;
	} else if (sign == 1) {
		for (i=flag_1; i<strlen(a); i++) {
			rec_max[strlen(a)-1-i] = a[i]-'0';
		} for (i=flag_2; i<strlen(b); i++) {
			rec_min[strlen(b)-1-i] = b[i]-'0';
		}
	} else if (sign == -1) {
		for (i=flag_2; i<strlen(b); i++) {
			rec_max[strlen(b)-1-i] = b[i]-'0';
		} for (i=flag_1; i<strlen(a); i++) {
			rec_min[strlen(a)-1-i] = a[i]-'0';
		}
	} for (i=0; i<100; i++) {
		res[i] += rec_max[i] - rec_min[i];
		if (res[i] < 0) {
			res[i+1]--;
			res[i]+=10;
		}
	} int flag;
	if (sign == 1) {
		flag = 0;
		for (i=99; i>=0 ;i--) {
			if (res[i] != 0) {
				flag = 1;
			} if (flag == 1) {
				printf("%d", res[i]);
			}
		}
	} else if (sign == -1) {
		flag = 0;
		printf("-");
		for (i=99; i>=0; i--) {
			if (res[i] != 0) {
				flag = 1;
			} if (flag == 1) {
				printf("%d", res[i]);
			}
		}
	}
	return 0;
}

