#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct t {
	char site[30];
	int distance;
}place[70];

struct carriage {
	char num[5];
	char site[30];
	int distance;
	int flag;
}a[70], b[70], c[70], blank;

int main() {
	int cnt = 0;
	int place_top = -1, a_top = -1, b_top = -1, c_top = -1;
	int n;
	int mark;
	scanf("%d", &n);
	int i, j;
	for (i=0; i<n; i++) {
		++place_top;
		scanf("%s%d", place[place_top].site, &place[place_top].distance);
	} scanf("%d", &n);
	for (i=0; i<n; i++) {
		++a_top;
		scanf("%s%s", a[a_top].num, a[a_top].site); 
		for (j=0; j<=place_top; j++) {
			if (strcmp(a[a_top].site, place[j].site) == 0) {
				a[a_top].distance = place[j].distance;
				break;
			}
		}
	} int max;
	int maxCarriage;
	for (i=0; i<n; i++) {
		b[++b_top] = a[a_top];
		a[a_top--] = blank;
	} int pos;
	while (b_top != -1) {
		mark = 0;
		for (pos=b_top; pos>=0; pos--) {
			if (pos == b_top) {
				max = b[pos].distance;
				maxCarriage = pos;
				continue;
			} if (b[pos].distance > max) {
				max = b[pos].distance;
				maxCarriage = pos;
			}
		} int tmp_b_top = b_top; 
		for (i=tmp_b_top; i>=maxCarriage; i--) {
			a[++a_top] = b[b_top];
			b[b_top--] = blank;
			cnt++;
		} if (a_top == 0) {
			a[a_top].flag = 1;
			continue;
		} else if (a_top > 0){
			for (i=a_top-1; i>=0; i--) {
				if (a[i].flag == 0) {
					mark = 1;
					break;
				}
			} if (mark == 1) {
				c[++c_top] = a[a_top];
				a[a_top--] = blank;
				while (a_top != -1 && a[a_top].flag == 0) {
					b[++b_top] = a[a_top];
					a[a_top--] = blank;
				} a[++a_top] = c[c_top];
				c[c_top--] = blank;
				cnt++;
			} a[a_top].flag = 1;
		}
	} for (i=0; i<=a_top; i++) {
		printf("%s ",a[i].num);
	} printf("\n%d", cnt);
	return 0;
}

