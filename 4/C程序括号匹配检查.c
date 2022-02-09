#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
char tmp[1024];

struct inf {
	char symbol;
	int line;
}rec[1000], stack[1000];

int main() {
	int tag = 0;
	FILE *in;
	in = fopen("example.c", "r");
	int nowLine = 0;
	int flag = 0; //0代表有效 1代表单行注释 2代表多行注释 3代表引号 4代表字符常量 
	int top = -1;
	int i;
	int nowLen;
	while (fgets(tmp, 1024, in) != NULL) {
		nowLen = strlen(tmp);
		if (flag == 1) {
			flag = 0;
		} nowLine++;
		for (i=0; i<nowLen; i++) {
			if (flag == 0 && (tmp[i] == '(' || tmp[i] == ')' || tmp[i] == '{' || tmp[i] == '}')) {
				rec[++top].symbol = tmp[i];
				rec[top].line = nowLine;
			} if (flag == 0 && tmp[i] == '/' && tmp[i+1] == '/') {
				flag = 1;
			} if (flag == 0 && tmp[i] == '/' && tmp[i+1] == '*') {
				flag = 2;
			} if (flag == 2 && tmp[i] == '*' && tmp[i+1] == '/') {
				flag = 0;
			} if (flag == 0 && tmp[i] == '"') {
				flag = 3;
			} else if (flag == 3 && tmp[i] == '"') {
				flag = 0;
			} if (flag == 0 && tmp[i] == '\'') {
				flag = 4;
			} else if (flag == 4 && tmp[i] == '\'') {
				flag = 0;
			}
		}
	} int stack_top = -1;
	for (i=0; i<=top; i++) {
		if (rec[i].symbol == '(' || (rec[i].symbol == '{' && stack_top == -1) || (rec[i].symbol == '{' && stack_top != -1 && stack[stack_top].symbol != '(')) {
			stack[++stack_top].symbol = rec[i].symbol;
			stack[stack_top].line = rec[i].line;
		} else if (rec[i].symbol == '{' && stack_top != -1 && stack[stack_top].symbol == '(') {
			tag = 1;
			printf("without maching '%c' at line %d\n", stack[stack_top].symbol, stack[stack_top].line);
			break;
		}  else if (rec[i].symbol == ')') {
			if (stack[stack_top].symbol == '(') {
				stack[stack_top].symbol = '\0';
  				stack[stack_top].line = 0;
				stack_top--;
			} else {
				tag = 1;
				printf("without maching '%c' at line %d\n", rec[i].symbol, rec[i].line);
				break;
			}
		} else if (rec[i].symbol == '}') {
			if (stack[stack_top].symbol == '{') {
				stack[stack_top].symbol = '\0';
  				stack[stack_top].line = 0;
				stack_top--;
			} else {
				tag = 1;
				printf("without maching '%c' at line %d\n", rec[i].symbol, rec[i].line);
				break;
			}
		}
	} while (tag == 0 && stack_top > -1) {
		tag = 1;
		printf("without maching '%c' at line %d\n", stack[stack_top].symbol, stack[stack_top].line);
		break;
		stack[stack_top].symbol = '\0';
		stack[stack_top].line = 0;
		stack_top--;
	} if (tag == 0) {
		for (i=0; i<=top; i++) {
			printf("%c", rec[i].symbol);
		}
	}
	return 0;
}

