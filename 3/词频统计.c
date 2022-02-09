#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct chart {
	char word[30];
	int cnt;
}a[1000], rec;

char tmp[1024];
char tmp_word[30];

int main() {
	FILE *in;
	in = fopen("article.txt", "r");
	int i, j;
	int len;
	int pos;
	int a_pos = 0;
	int tag = 0;
	while (fgets(tmp, 1024, in) != NULL) {
		len = strlen(tmp);
		for (i=0; i<len; i++) {
			if (tmp[i] >= 'A' && tmp[i] <= 'Z') {
				tmp[i] += ('a'-'A');
			}
		} pos = -1;
		for (i=0; i<len; i++) {
			if (tmp[i] >= 'a' && tmp[i] <= 'z') {
				tmp_word[++pos] = tmp[i];
			} if ((!(tmp[i] >= 'a' && tmp[i] <= 'z') && pos != -1) || ((tmp[i] >= 'a' && tmp[i] <= 'z')) && tmp[i+1] == 0) {
				for (j=0; j<a_pos; j++) {
					if (strcmp(tmp_word, a[j].word) == 0) {
						tag = 1;
						break;
					}
				} if (tag == 0) {
					strcat(a[a_pos].word, tmp_word);
					a[a_pos++].cnt = 1;
				} else if (tag == 1) {
					a[j].cnt++;
					tag = 0;
				} memset(tmp_word, 0, sizeof(tmp_word));
				pos = -1;
			} 
		}
	} 
	for (i=a_pos-1; i>0; i--) {
		for (j=0; j<i; j++) {
			if (strcmp(a[j].word, a[j+1].word) > 0) {
				rec = a[j];
				a[j] = a[j+1];
				a[j+1] = rec;
			}
		}
	} for (i=0; i<a_pos; i++) {
		printf("%s %d\n", a[i].word, a[i].cnt);
	} 
	return 0;
} 

