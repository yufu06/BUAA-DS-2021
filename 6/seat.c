#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct chart {
    char num[20];
    char name[30];
    int seat;
}rec[110], tmp_rec;
char line[1024];
int main () {
	FILE *in, *out;
    in = fopen("in.txt", "r");
    out = fopen("out.txt", "w");
    int n;
    scanf("%d", &n);
    int i, j, k;
    for (i=0; i<n; i++) {
        fgets(line, 1024, in);
        sscanf(line, "%s%s%d", rec[i].num, rec[i].name, &rec[i].seat);
    } for (j=n-1; j>0; j--) {
        for (i=0; i<j; i++) {
            if (rec[i].seat > rec[i+1].seat) {
                tmp_rec = rec[i];
                rec[i] = rec[i+1];
                rec[i+1] = tmp_rec;
            }
        }
    } int min = (n < rec[n-1].seat) ? n : rec[n-1].seat;
    int flag;
    int minus = -1;
    for (i=1; i<=min; i++) {
        flag = 0;
        for (j=0; j<n; j++) {
            if (rec[j].seat == i) {
                flag = 1;
            }
        } if (flag == 0) {
            minus++;
            if(rec[n-1-minus].seat > i) {
                rec[n-1-minus].seat = i;
            }
        }
    } for (i=1; i<=min; i++) {
        flag = 0;
        int max = 0;
        for (j=0; j<n; j++) {
            if (rec[j].seat > max) {
                max = rec[j].seat;
            }
        } for (j=0; j<n; j++) {
            if (rec[j].seat == i) {
                flag++;
                if (flag >= 2) {
                    max++;
                    rec[j].seat = max;
                }
            }
        }
    } for (j=n-1; j>0; j--) {
        for (i=0; i<j; i++) {
            if (strcmp(rec[i].num, rec[i+1].num) > 0) {
                tmp_rec = rec[i];
                rec[i] = rec[i+1];
                rec[i+1] = tmp_rec;
            }
        }
    } for (i=0; i<n; i++) {
        memset(line, 0, sizeof (line));
        strcat(line, rec[i].num);
        strcat(line, " ");
        strcat(line, rec[i].name);
        strcat(line, " ");
        char tmp_num[20] = "";
        int tmp_num_pos = -1;
        int tmp_seat = rec[i].seat;
        while (tmp_seat != 0) {
            tmp_num[++tmp_num_pos] = (tmp_seat % 10 + '0');
            tmp_seat /= 10;
        } tmp_num[tmp_num_pos+1] = 0;
        for (j=0, k=tmp_num_pos; j<k; j++, k--) {
            char change = tmp_num[j];
            tmp_num[j] = tmp_num[k];
            tmp_num[k] = change;
        } strcat(line, tmp_num);
        strcat(line, "\n");
        fputs(line, out);
    }
	return 0;
}