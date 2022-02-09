#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

struct line {
    int index;
    int vi;
    int vj;
}a[1010];
int a_top = -1;
int n, e;
int origin_path[1010];
int origin_flag[1010];

int isCircle(int path[], int flag[], int top) {
    int i, j;
    int mark[1010];
    for (i=0; i<1010; i++) {
        mark[i] = 0;
    } for (i=0; i<=top; i++) {
        for (j=0; j<=a_top; j++) {
            if (a[j].index == path[i]) {
                break;
            }
        } if (flag[i] == 1) {
            mark[a[j].vi]++;
        } else {
            mark[a[j].vj]++;
        }
    } for (i=0; i<1010; i++) {
        if (mark[i] > 1) {
            return 1;
        }
    } return 0;
}

int isRepeated(int path[], int flag[], int top, int v) {
    int i, j;
    int mark[1010];
    for (i=0; i<1010; i++) {
        mark[i] = 0;
    } for (i=0; i<=top; i++) {
        for (j=0; j<=a_top; j++) {
            if (a[j].index == path[i]) {
                break;
            }
        } if (flag[i] == 1) {
            mark[a[j].vi]++;
        } else {
            mark[a[j].vj]++;
        }
    } if (mark[v] > 0) {
        return 1;
    } return 0;
}


void DFS(int origin, int path[], int flag[], int top) {
    if (origin == n-1 && isCircle(path, flag, top) == 0) {
        int i;
        for (i=0; i<=top; i++) {
            printf("%d", path[i]);
            if (i<top) {
                printf(" ");
            } else {
                printf("\n");
            }
        } return;
    } int i, j;
    for (i=0; i<=a_top; i++) {
        if ((a[i].vi == origin && isRepeated(path, flag, top, a[i].vj) == 0) || (a[i].vj == origin && isRepeated(path, flag, top, a[i].vi) == 0)) {
            int *tmp_path = (int *) malloc (sizeof (int) * (top + 10));
            int *tmp_flag = (int *) malloc (sizeof (int) * (top) + 10);
            int tmp_top = top;
            for (j=0; j<=top; j++) {
                tmp_path[j] = path[j];
                tmp_flag[j] = flag[j];
            } tmp_path[++tmp_top] = a[i].index;
            if (a[i].vi == origin && isRepeated(path, flag, top, a[i].vj) == 0) {
                tmp_flag[tmp_top] = 1;
                DFS(a[i].vj, tmp_path, tmp_flag, tmp_top);
            } else {
                tmp_flag[tmp_top] = 2;
                DFS(a[i].vi, tmp_path, tmp_flag, tmp_top);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &e);
    int i;
    for (i=0; i<e; i++) {
        ++a_top;
        scanf("%d%d%d", &a[a_top].index, &a[a_top].vi, &a[a_top].vj);
    } DFS(0, origin_path, origin_flag, -1);
    return 0;
}