#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
int s[110];
int main() {
	int type;
	int num;
	int top = -1;
	while (scanf("%d", &type) != EOF) {
		if (type == 1) {
			if (top == 100) {
				printf("error ");
			} else {
				scanf("%d ", &num);
				s[++top] = num;
			}
		} else if (type == 0) {
			if (top == -1) {
				printf("error ");
			} else {
				printf("%d ", s[top--]);
			}
		} else if (type == -1) {
			break;
		}
	}
	return 0;
}

