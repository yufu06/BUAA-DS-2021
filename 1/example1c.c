#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

char a[100];
char b[100];
int num[100];
char stack[100];
char rec[10];

int judge(char c) {
	if (c == '+' || c == '-') {
		return 1;
	} else if (c == '*' || c== '/') {
		return 2;
	} return -1;
}

int a_to_i (char rec[], int tmp) {
	int i;
	tmp = 0;
	for (i = 0; i < strlen(rec); i++) {
		tmp += (rec[i]-'0') * pow(10, strlen(rec)-1-i);
	} return tmp;
}

int main() {
	gets(a);
	int i;
	int k = 0;
	int tmp;
	for (i = 0; i < strlen(a); i++) {
		if (a[i] == ' ') {
			continue;
		} else {
			b[k++] = a[i];
		}
	} int flag_num = -1;
	int flag_stack = -1;
	int flag_rec = -1;
	for (i = 0; i < strlen(b); i++) {
		if (b[i] >= '0' && b[i] <= '9') {
			rec[++flag_rec] = b[i];
		} else {
			num[++flag_num] = a_to_i(rec, tmp);
			memset(rec, 0, sizeof(rec));
			flag_rec = -1;
			if (i == strlen(b)-1) {
				continue;
			} if (flag_stack == -1) {
				stack[++flag_stack] = b[i];
			} else {
				while(flag_stack != -1 && judge(stack[flag_stack]) >= judge(b[i])) {
					int res;
					if (stack[flag_stack] == '+') {
						res = num[flag_num-1] + num[flag_num];
					} else if (stack[flag_stack] == '-') {
						res = num[flag_num-1] - num[flag_num];
					} else if (stack[flag_stack] == '*') {
						res = num[flag_num-1] * num[flag_num];
					} else if (stack[flag_stack] == '/') {
						res = num[flag_num-1] / num[flag_num];
					} num[flag_num--] = 0;
					num[flag_num] = res;
					flag_stack--;
				} stack[++flag_stack] = b[i];
			}
		}
	} while (flag_stack != -1) {
		int res;
		if (stack[flag_stack] == '+') {
		res = num[flag_num-1] + num[flag_num];
		} else if (stack[flag_stack] == '-') {
		res = num[flag_num-1] - num[flag_num];
		} else if (stack[flag_stack] == '*') {
		res = num[flag_num-1] * num[flag_num];
		} else if (stack[flag_stack] == '/') {
		res = num[flag_num-1] / num[flag_num];
		} num[flag_num--] = 0;
		num[flag_num] = res;
		flag_stack--;	
	} printf("%d", num[0]);
	return 0;
}



