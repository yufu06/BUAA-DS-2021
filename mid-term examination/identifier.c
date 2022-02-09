#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
char input[500];
char rec[100][100];
char tmp[100];
int main () {
	int line = -1;
    int top = -1;
    int flag = 0;
    gets(input);
    int len = strlen(input);
    int i, j;
    for (i=0; i<len; i++) {
        if (!(input[i] == '_' || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= '0' && input[i] <= '9'))) {
            input[i] = ' ';
        }
    }
    for (i=0; i<len; i++) {
        if (input[i] != ' ') {
            tmp[++top] = input[i];
        } if ((input[i] == ' ' && top != -1) || (i == len-1 && top != -1)) {
            for (j=0; j<=top; j++) {
                if ((tmp[j] >= 'a' && tmp[j] <= 'z') || (tmp[j] >= 'A' && tmp[j] <= 'Z')) {
                    flag = 1;
                    break;
                }
            } 
            for (j=0; j<=line; j++) {
                if (strcmp(rec[j], tmp) == 0) {
                    flag = 2;
                }
            }
            if (flag == 1) {
                    ++line;
                    strcpy(rec[line], tmp);
                    memset(tmp, 0, sizeof (tmp));
                    top = -1;
                    flag = 0;
            } else {
                memset(tmp, 0, sizeof (tmp));
                    top = -1;
                    flag = 0;
            }
        }
    }
    for (j=line; j>0; j--) {
        for (i=0; i<j; i++) {
            if (strcmp(rec[i], rec[i+1]) > 0) {
                char t[100];
                strcpy(t, rec[i]);
                memset(rec[i], 0, sizeof (rec[i]));
                strcpy(rec[i], rec[i+1]);
                memset(rec[i+1], 0, sizeof (rec[i+1]));
                strcpy(rec[i+1], t);
                memset(t, 0, sizeof (t));
            }
        }
    }
    for (i=0; i<=line; i++) {
        printf("%s", rec[i]);
        if (i != line) {
            printf(" ");
        }
    }
	return 0;
}