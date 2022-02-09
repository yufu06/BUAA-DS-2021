#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

int judge(char s[], char t[]) {  //在s串中查找t串，成功查找返回字串起始位置，否则返回-1 
	int i, j;
	char tmp_1[50];
	char tmp_2[50];
	strcpy(tmp_1, s);
	strcpy(tmp_2, t);
	for (i=0; i<strlen(tmp_1); i++) {
		if (tmp_1[i] >= 'A' && tmp_1[i] <= 'Z') {
			tmp_1[i] += 32;
		}
	} for (i=0; i<strlen(tmp_2); i++) {
		if (tmp_2[i] >= 'A' && tmp_2[i] <= 'Z') {
			tmp_2[i] += 32;
		}
	} for (i=0; i<strlen(tmp_1);i++) {
		for (j=0; j<strlen(tmp_2); j++) {
			if (i+j < strlen(tmp_1) && tmp_1[i+j] != tmp_2[j]) {
				break;
			} if (i+j < strlen(tmp_1) && j == strlen(tmp_2)-1) {
				return i;
			} 
		}
	} return -1;
}

char pre[50];
char aft[50];
char tmp[1024];

int main() {
	gets(pre);
	gets(aft);
	FILE *in, *out;
	in = fopen("filein.txt", "r");
	out = fopen("fileout.txt", "w");
	while (fgets(tmp, 1024, in) != NULL) {
		int i, j;
		for (i=0; i<strlen(tmp); i++) {
			if (judge(tmp+i, pre) == 0) {
				for (j=0; j<strlen(aft); j++) {
					fputc(aft[j], out);
				} i += (strlen(pre)-1);
			} else {
				fputc(tmp[i], out);
			}
		}
	} fclose(in);
	fclose(out);
	return 0;
}

