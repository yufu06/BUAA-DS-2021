#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
char pre[200];
char aft[200];
int numStack[100];
char symStack[100];
char rec[100];
char flag[10];
int a_to_i(char tmp[]) {
	int flag;
	int len = strlen(tmp);
	int i;
	int res = 0;
	for (i=0; i<len; i++) {
		res += (tmp[i]-'0') * pow(10, len-1-i);
	} return res;
}
int judge(char sym) {
	if (sym == '+' || sym == '-') return 1;
	else return 2;
}
int main() {
	int num_top = -1;
	int sym_top = -1;
	int pos = -1;
	gets(pre);
	int len = strlen(pre)-1;
	int i;
	for (i=0; i<len; i++) {
		if (pre[i] == ' ') continue;
		if (pre[i] >= '0' && pre[i] <= '9') {
			rec[++pos] = pre[i];
			if ((i == len-1 && pos != -1) || pre[i+1] == ' ') {
				strcat(aft, rec);
				strcat(aft, " ");
				memset(rec, 0, sizeof (rec));
				pos = -1;
			}
		} else {
			if (pos != -1 || i == len-1) {
				strcat(aft, rec);
				strcat(aft, " ");
				memset(rec, 0, sizeof (rec));
				pos = -1;
			} if (sym_top == -1 || pre[i] == '(') {
				symStack[++sym_top] = pre[i];
				continue;
			} if (pre[i] == ')') {
				while (sym_top != -1 && symStack[sym_top] != '(') {
					flag[0] = symStack[sym_top--];
					strcat(aft, flag);
					strcat(aft, " ");
					memset(flag, 0, sizeof (flag));
				} sym_top--;
				continue;
			} while (sym_top != -1 && symStack[sym_top] != '(' && judge(pre[i]) <= judge(symStack[sym_top])) {
				flag[0] = symStack[sym_top--];
				strcat(aft, flag);
				strcat(aft, " ");
				memset(flag, 0, sizeof (flag));
			} symStack[++sym_top] = pre[i];
		}
	} while (sym_top != -1) {
		flag[0] = symStack[sym_top--];
		strcat(aft, flag);
		strcat(aft, " ");
		memset(flag, 0, sizeof (flag));
	} len = strlen(aft);
	pos = -1;
	for (i=0; i<len; i++) {
		if (pos == -1 && aft[i] == ' ') continue;
		if (aft[i] >= '0' && aft[i] <= '9') {
			rec[++pos] = aft[i];
		} else {
			if (pos != -1) {
				numStack[++num_top] = a_to_i(rec);
				memset(rec, 0, sizeof(rec));
				pos = -1;
			} if (aft[i] == '+') {
				numStack[num_top-1] = numStack[num_top] + numStack[num_top-1];
				num_top--;
			} else if (aft[i] == '-') {
				numStack[num_top-1] = numStack[num_top-1] - numStack[num_top];
				num_top--;
			} else if (aft[i] == '*') {
				numStack[num_top-1] = numStack[num_top-1] * numStack[num_top];
				num_top--;
			} else if (aft[i] == '/') {
				numStack[num_top-1] = numStack[num_top-1] / numStack[num_top];
				num_top--;
			} else if (aft[i] == '%') {
				numStack[num_top-1] = numStack[num_top-1] % numStack[num_top];
				num_top--;
			}
		}
	} printf("%d", numStack[0]);
	return 0;
}

