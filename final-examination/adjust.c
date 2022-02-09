#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct chart {
    int num;
    int isGate;
    int childrenNum[200];
    int childrenTop;
    int newNum;
}inf[100000];

struct table {
    int num;
    int sum;
}window[1000], tmpWindow;
int windowTop = -1;
int markTop = -1;

int queue[100000];

int mark[10000];

int main () {
	int i, j;
    for (i=0; i<100000; i++) {
        inf[i].childrenTop = -1;
    } int tmpNum;
    int tmpChildrenNum;
    int maxWindow = 0;
    while (1) {
        scanf("%d", &tmpNum);
        if (tmpNum == -1) break;
        while (1) {
            scanf("%d", &tmpChildrenNum);
            if (tmpChildrenNum == -1) break;
            if (tmpChildrenNum < 100) {
                inf[tmpChildrenNum].isGate = 1;
                if (maxWindow < tmpChildrenNum) {
                    maxWindow = tmpChildrenNum;
                }
            } inf[tmpNum].childrenNum[++inf[tmpNum].childrenTop] = tmpChildrenNum;
        }
    } for (i=1; i<=maxWindow; i++) {
        ++windowTop;
        scanf("%d%d", &window[windowTop].num, &window[windowTop].sum);
    } for (j=windowTop; j>0; j--) {
        for (i=0; i<j; i++) {
            if ((window[i].sum < window[i+1].sum) || (window[i].sum == window[i+1].sum && window[i].num > window[i+1].num)) {
                tmpWindow = window[i];
                window[i] = window[i+1];
                window[i+1] = tmpWindow;
            }
        }
    } int head = 0;
    int rear = 0;
    queue[rear++] = 100;
    while (head != rear) {
        int tmp = queue[head++];
        if (tmp < 100) {
            mark[++markTop] = tmp;
            inf[tmp].newNum = window[markTop].num;
        } for (i=0; i<=inf[tmp].childrenTop; i++) {
            queue[rear++] = inf[tmp].childrenNum[i];
        }
    } for (i=0; i<=markTop; i++) {
       printf("%d<-%d\n", mark[i], inf[mark[i]].newNum);
    }
	return 0;
}