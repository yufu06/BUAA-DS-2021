#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct option {
	int op;
	int pos;
	char str[100];
}pre[15];
char rec[100][520];
char keep[520];

int main() {
	gets(keep);
	int n;
	int len;
	scanf("%d", &n);
	int top = n;
	strcpy(rec[top], keep);
	int i, j, k;
	for (i=n-1; i>=0; i--) {
		scanf("%d%d%s", &pre[i].op, &pre[i].pos, pre[i].str);
	} for (i=0; i<n; i++) {
		len = strlen(rec[top-i]);
		if (pre[i].op == 1) {
			j = 0, k = 0;
			for (k=0; k<len; ) {
				if (k == pre[i].pos) {
					k += strlen(pre[i].str);
				} rec[top-i-1][j++] = rec[top-i][k++];
			}
		} else if (pre[i].op == 2) {
			j = 0, k = 0;
			for (k=0; k<len; ) {
				if (j == pre[i].pos) {
					strcat(rec[top-i-1], pre[i].str);
					j += strlen(pre[i].str);
				} rec[top-i-1][j++] = rec[top-i][k++];
			}
		}
	} getchar();
	int flag;
	int pos;
	int num;
	char add[520];
	while (scanf("%d", &flag) != EOF) {
		len = strlen(rec[top]);
		if (flag == 1) {
			top++;
			scanf("%d%s", &pos, add);
			j = 0, k = 0;
			for (j=0; j<len; j++) {
				if (j == pos) {
					strcat(rec[top], add);
					k += strlen(add);
				} rec[top][k++] = rec[top-1][j];
			} if (pos == len) {
				strcat(rec[top], add);
			}
		} else if (flag == 2) {
			top++;
			scanf("%d%d", &pos, &num);
			j = 0, k = 0;
			for (j=0; j<len; j++) {
				if (j == pos) {
					j+=num;
				} if (j < len) {
					rec[top][k++] = rec[top-1][j];
				}
			}
		} else if (flag == 3) {
			if (top == 0) continue;
			memset(rec[top], 0, sizeof(rec[top]));
			top--; 
		} else if (flag == -1) {
			break;
		}
	} printf("%s", rec[top]);
	return 0;
}

