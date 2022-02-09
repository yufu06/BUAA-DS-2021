#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

struct chart {
	char name[25];
	char phone[15];
	int cnt;
}inf[110], tmp;

int main() {
	int n;
	scanf("%d", &n);
	int i, j=0, k;
	for (i=0; i<n; i++) {
		int flag = 0;
		char tmp_name[25], tmp_phone[15];
		scanf("%s %s", tmp_name, tmp_phone);
		for (k=0; k<j; k++) {
			if (strcmp(tmp_name, inf[k].name) == 0 && strcmp(tmp_phone, inf[k].phone) == 0) {
				flag = 1;
				break;
			} else if (strcmp(tmp_name, inf[k].name) == 0 && strcmp(tmp_phone, inf[k].phone) != 0) {
				flag = 2;
				break;
			}
		} if (flag == 0) {
			strcpy(inf[j].name, tmp_name);
			strcpy(inf[j].phone, tmp_phone);
			inf[k].cnt++;
			j++;
		} else if (flag == 1) {
			continue;
		} else if (flag == 2) {
			char tmp_cnt[3];
			tmp_cnt[0] = '_';
			tmp_cnt[1] = inf[k].cnt + '0';
			tmp_cnt[2] = 0;
			inf[k].cnt++;
			strcat(tmp_name, tmp_cnt);
			strcpy(inf[j].name, tmp_name);
			strcpy(inf[j].phone, tmp_phone);
			j++;
		}
	} int a, b;
	for (b=j-1; b>0; b--) {
		for (a=0; a<b; a++) {
			if (strcmp(inf[a].name, inf[a+1].name) > 0) {
				tmp = inf[a];
				inf[a] = inf[a+1];
				inf[a+1] = tmp;
			}
		}
	} for (k=0; k<j; k++) {
		printf("%s %s\n", inf[k].name, inf[k].phone);
	}
	return 0;
}

