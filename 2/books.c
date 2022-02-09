#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

struct book {
	char name[60];
	char author[30];
	char press[40];
	char date[20];
}a[510], blank, keep;

char tmp[1024];

int main() {
	FILE *in = NULL, *out = NULL;
	in = fopen("books.txt", "r");
	out = fopen("ordered.txt", "w");
	int pos = -1;
	int type;
	while (fgets(tmp, 1024, in) != NULL) {
		++pos;
		sscanf(tmp, "%s%s%s%s", a[pos].name, a[pos].author, a[pos].press, a[pos].date);
	} int i, j;
	for (i=pos; i>0; i--) {
		for (j=0; j<i; j++) {
			if (strcmp(a[j].name, a[j+1].name)>0) {
				keep = a[j];
				a[j] = a[j+1];
				a[j+1] = keep;
			}
		}
	} while (scanf("%d", &type) != EOF) {
		getchar();
		if (type == 1) {
			gets(tmp);
			sscanf(tmp, "%s%s%s%s", keep.name, keep.author, keep.press, keep.date);
			for (i=pos; i>=0; i--) {
				if (strcmp(keep.name, a[i].name)>0) {
					break;
				}
			} if (i == pos) {
				pos++;
				a[pos] = keep;
			} else{
				pos++;
				for (j=pos; j>=i+2; j--) {
					a[j] = a[j-1];
				} a[i+1] = keep;
			}
		} else if (type == 2) {
			gets(tmp);
			sscanf(tmp, "%s", keep.name);
			for (i=0; i<=pos; i++) {
				if (strstr(a[i].name, keep.name) != NULL) {
					printf("%-50s%-20s%-30s%-10s\n", a[i].name, a[i].author, a[i].press, a[i].date);
				}
			}
		} else if (type == 3) {
			gets(tmp);
			sscanf(tmp, "%s", keep.name);
			for (i=0; i<=pos; i++) {
				if (strstr(a[i].name, keep.name) != NULL) {
					a[i] = blank; 
				}
			} for (i=0, j=-1; i<=pos; i++) {
				if (a[i].name[0] != '\0') {
					++j;
					a[j] = a[i];
				}
			} pos = j;
		} else if (type == 0) {
			for (i=0; i<=pos; i++) {
				sprintf(tmp, "%-50s%-20s%-30s%-10s", a[i].name, a[i].author, a[i].press, a[i].date);
				fputs(tmp, out);
				fputc('\n', out);
			} break;
		}
	} fclose(in);
	fclose(out);
	return 0;
}

