#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct chart {
    char time[100];
    int computerNum;
    int stuNum;
    char name[30];
}person[250];
int error[250];
int errorTop = -1;
int resTop = -1;
struct res {
    int stuNum;
    char name[30];
}res[250], tmpRes;

int main () {
	int n;
    scanf("%d", &n);
    int i, j;
    for (i=0; i<n; i++) {
        scanf("%s%d%d%s", person[i].time, &person[i].computerNum, &person[i].stuNum, person[i].name);
        for (j=0; j<i; j++) {
            if (person[j].stuNum == person[i].stuNum && person[j].computerNum != person[i].computerNum) {
                error[++errorTop] = i;
            }
        }
    } for (i=0; i<=errorTop; i++) {
        int flag = 0;
        for (j=0; j<i; j++) {
            if (person[error[j]].stuNum == person[error[i]].stuNum) {
                flag = 1;
            }
        } if (flag == 0) {
            res[++resTop].stuNum = person[error[i]].stuNum;
            strcpy(res[resTop].name, person[error[i]].name);
        }
    } for (j=resTop; j>0; j--) {
        for (i=0; i<j; i++) {
            if (res[i].stuNum > res[i+1].stuNum) {
                tmpRes = res[i];
                res[i] = res[i+1];
                res[i+1] = tmpRes;
            }
        }
    } for (i=0; i<=resTop; i++) {
        printf("%d %s\n", res[i].stuNum, res[i].name);
    }
	return 0;
}