#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
	long long val;
	long long index;
} pol;

pol a[1000], b[1000], res[1000], ans[1000], change;
char tmp[1000];
char rec[1000];

long long a_to_i (char arr[]) {
	long long num = 0;
	int i;
	int len = strlen(arr);
	for (i=0; i<len; i++) {
		num += (arr[i] - '0') * pow(10, len-1-i);
	} return num;
}

int main() {
	int pos_a = -1;
	int pos_b = -1;
	gets(tmp);
	int len = strlen(tmp);
	int i, j;
	int pos_rec = -1;
	int flag = 2;
	for (i=0; i<len; i++) {
		if (tmp[i] >= '0' && tmp[i] <= '9') {
			rec[++pos_rec] = tmp[i];
		} if (tmp[i] == ' ' || i == len-1) {
			if (flag == 2) {
				a[++pos_a].val = a_to_i(rec);
				memset(rec, 0, sizeof(rec));
				pos_rec = -1;
				flag = 1;
			} else if (flag == 1) {
				a[pos_a].index = a_to_i(rec);
				memset(rec, 0, sizeof(rec));
				pos_rec = -1;
				flag = 2;
			}
		}
	} gets(tmp);
	len = strlen(tmp);
	pos_rec = -1;
	flag = 2;
	for (i=0; i<len; i++) {
		if (tmp[i] >= '0' && tmp[i] <= '9') {
			rec[++pos_rec] = tmp[i];
		} if (tmp[i] == ' ' || i == len-1) {
			if (flag == 2) {
				b[++pos_b].val = atoi(rec);
				memset(rec, 0, sizeof(rec));
				pos_rec = -1;
				flag = 1;
			} else if (flag == 1) {
				b[pos_b].index = atoi(rec);
				memset(rec, 0, sizeof(rec));
				pos_rec = -1;
				flag = 2;
			}
		}
	} int pos_res = -1;
	for (i=0; i<=pos_a; i++) {
		for (j=0; j<=pos_b; j++) {
			pos_res++;
			res[pos_res].val = a[i].val * b[j].val;
			res[pos_res].index = a[i].index + b[j].index;
		}
	} for (i=pos_res; i>0; i--) {
		for (j=0; j<i; j++) {
			if (res[j].index < res[j+1].index) {
				change = res[j];
				res[j] = res[j+1];
				res[j+1] = change;
			}
		}
	} int pos_ans = -1;
	for (i=0; i<=pos_res; i++) {
		if (pos_ans == -1 || res[i].index != ans[pos_ans].index) {
			pos_ans++;
			ans[pos_ans].val = res[i].val;
			ans[pos_ans].index = res[i].index;
		} else if (res[i].index == ans[pos_ans].index) {
			ans[pos_ans].val += res[i].val;
		}
	} for (i=0; i<=pos_ans; i++) {
		if (ans[i].val != 0) {
			printf("%lld %lld ", ans[i].val, ans[i].index);
		}
	}
	return 0;
}
