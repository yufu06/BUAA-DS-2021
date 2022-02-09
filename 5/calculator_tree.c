#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
char pre[1000]; //中缀
char aft[1000];	//后缀
char op_s[1000];
struct chart {
	int flag;
	int num;
	char op;
	struct chart *left, *right;
}*rec, *a[1000];
char tmp_num[1000];
int a_to_i (char tmp_num[]) {
	int i;
	int num = 0;
	int len = strlen(tmp_num);
	for (i=0; i<len; i++) {
		num += pow(10, len-1-i) * (tmp_num[i] - '0');
	} return num;
}
int cnt(struct chart *root) {
	if (root->left->flag == 2) {
		root->left->num = cnt(root->left);
	} if (root->right->flag == 2) {
		root->right->flag = 1;
		root->right->num = cnt(root->right);
	} root->flag = 1;
	if (root->op == '+') {
		root->num = root->left->num + root->right->num; 
	} else if (root->op == '-') {
		root->num = root->left->num - root->right->num; 
	} else if (root->op == '*') {
		root->num = root->left->num * root->right->num;
	} else if (root->op == '/') {
		root->num = root->left->num / root->right->num;
	} return root->num;
}
int judge(char op) {
	if (op == '+' || op == '-') return 1;
	else return 2;
}
int main () {
	gets(pre);
	int len = strlen(pre);
	int i;
	int pos = -1;
	int op_s_top = -1;
	int a_top = -1;
	int tmp_num_pos = -1;
	for (i=0; i<len; i++) {
		if (pre[i] == '=') break;
		if (pre[i] == ' ') continue;
		if (pre[i] >= '0' && pre[i] <= '9') {
			aft[++pos] = pre[i];
			continue;
		} else if (op_s_top == -1 || op_s[op_s_top] == '(' || pre[i] == '(') {
			aft[++pos] = ' ';
			op_s[++op_s_top] = pre[i];
			continue;
		} else if (pre[i] == ')') {
			aft[++pos] = ' ';
			while (op_s[op_s_top] != '(') {
				aft[++pos] = op_s[op_s_top--];
				aft[++pos] = ' ';
			} op_s_top--;
			continue;
		} aft[++pos] = ' ';
		while (op_s_top != -1 && op_s[op_s_top] != '(' && judge(op_s[op_s_top]) >= judge(pre[i])) {
			aft[++pos] = op_s[op_s_top--];
			aft[++pos] = ' ';
		} op_s[++op_s_top] = pre[i];
	} aft[++pos] = ' ';
	while (op_s_top != -1) {
		aft[++pos] = op_s[op_s_top--];
		if (op_s_top != 0) {
			aft[++pos] = ' ';
		}
	} len = strlen(aft);
	for (i=0; i<len; i++) {
		if (aft[i] >= '0' && aft[i] <= '9') {
			tmp_num[++tmp_num_pos] = aft[i];
		} else if (aft[i] == ' ' && tmp_num_pos != -1) {
			++a_top;
			rec = (struct chart *) malloc (sizeof (struct chart));
			rec->flag = 1;
			rec->num = a_to_i(tmp_num);
			memset(tmp_num, 0, sizeof (tmp_num));
			tmp_num_pos = -1;
			a[a_top] = rec;
		} else if (aft[i] != ' ') {
			rec = (struct chart *) malloc (sizeof (struct chart));
			rec->flag = 2;
			rec->op = aft[i];
			rec->right = a[a_top];
			rec->left = a[a_top-1];
			a[--a_top] = rec;
		}
	} if (a[a_top] != NULL) {
		printf("%c", a[a_top]->op);
		if (a[a_top]->left != NULL) {
			if (a[a_top]->left->flag == 1) {
				printf(" %d", a[a_top]->left->num);
			} else {
				printf(" %c", a[a_top]->left->op);
			}
		} if (a[a_top]->right != NULL) {
			if (a[a_top]->right->flag == 1) {
				printf(" %d", a[a_top]->right->num);
			} else {
				printf(" %c", a[a_top]->right->op);
			}
		} printf("\n");
	} int res = cnt(a[a_top]);
	printf("%d", res);
	return 0;
}