#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct a {
	int l_x, l_y, r_x, r_y;
	int to;
}line[105];



int main() {
	int n;
	scanf("%d", &n);
	int i, j;
	for (i=0; i<n; i++) {
		scanf("%d%d%d%d", &line[i].l_x, &line[i].l_y, &line[i].r_x, &line[i].r_y);
		line[i].to = -1;
	} for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			if (j == i) continue;
			if (line[i].r_x == line[j].l_x && line[i].r_y == line[j].l_y) {
				line[i].to = j;
				break;
			}
		}
	} int mark = 0;
	int max_cnt;
	int max_l_x;
	int max_l_y;
	int tmp, cnt;
	for (i=0; i<n; i++) {
		cnt = 1;
		tmp = i;
		while (line[tmp].to != -1) {
			cnt++;
			tmp = line[tmp].to;
		} if (mark == 0) {
			max_cnt = cnt;
			max_l_x = line[i].l_x;
			max_l_y = line[i].l_y;
			mark = 1;
		} else if (mark == 1) {
			if (cnt > max_cnt) {
				max_cnt = cnt;
				max_l_x = line[i].l_x;
				max_l_y = line[i].l_y;
			}
		}
	} printf("%d %d %d", max_cnt, max_l_x, max_l_y);
	return 0;
}

