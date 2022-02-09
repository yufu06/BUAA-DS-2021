#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
char pre[30];
char aft[30];
char password[60];
char tmp[1024];
int main() {
	int i, j, pos = -1, flag;
	gets(password);
	for (i=0; i<26; i++) {
		pre[i] = 'a'+i;
	} for (i=0; i<strlen(password); i++) {
		int flag = 0;
		for (j=0; j<=pos; j++) {
			if (password[i] == aft[j]) {
				flag = 1;
				break;
			}
		} if (flag == 0) {
			aft[++pos] = password[i];
		}
	} for (i=25; i>=0; i--) {
		flag = 0;
		for (j=0; j<=pos; j++) {
			if (aft[j] == 'a'+i) {
				flag = 1;
				break;
			}
		} if (flag == 0) {
			aft[++pos] = 'a'+i;
		}
	} FILE *in, *out;
	in = fopen("encrypt.txt", "r");
	out = fopen("output.txt", "w");
	while (fgets(tmp, 1024, in) != NULL) {
		for (i=0; i<strlen(tmp); i++) {
			if (tmp[i] >= 'a' && tmp[i] <= 'z') {
				for (j=0; j<strlen(pre); j++) {
					if (tmp[i] == pre[j]) {
						fputc(aft[j], out);
						break;
					}
				}
			} else {
				fputc(tmp[i], out);
			}
		}
	} fclose(in);
	fclose(out);
	return 0;
}

