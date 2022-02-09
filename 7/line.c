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
    int weight;
}a[1010];
int rec[1010];
int rec_top = -1;
int collected[1010];
int collected_top = -1;
int judge(int v, int collected[], int collected_top) {
    int i;
    for (i=0; i<=collected_top; i++) {
        if (v == collected[i]) {
            return 1;
        }
    } return 0;
}
int main () {
	int n, e;
    int sum = 0;
    scanf("%d%d", &n, &e);
    int i, j;
    for (i=0; i<e; i++) {
        scanf("%d%d%d%d", &a[i].index, &a[i].vi, &a[i].vj, &a[i].weight);
    }
    collected[++collected_top] = 0;
    while (collected_top != n-1) {
        int tmp_index = 0;
        int tmp_weight = 0xffffff;
        for (i=0; i<=collected_top; i++) {
            for (j=0; j<e; j++) {
                if (((a[j].vi == collected[i] && judge(a[j].vj, collected, collected_top) == 0) || (a[j].vj == collected[i] && judge(a[j].vi, collected, collected_top) == 0)) && a[j].weight < tmp_weight) {
                    tmp_index = j;
                    tmp_weight = a[j].weight;
                }
            }
        } rec[++rec_top] = a[tmp_index].index;
        sum += tmp_weight;
        if (judge(a[tmp_index].vi, collected, collected_top) == 0) {
            collected[++collected_top] = a[tmp_index].vi;
        } else {
            collected[++collected_top] = a[tmp_index].vj;
        }
    } for (j=rec_top; j>0; j--) {
        for (i=0; i<j; i++) {
            if (rec[i] > rec[i+1]) {
                int tmp_rec = rec[i];
                rec[i] = rec[i+1];
                rec[i+1] = tmp_rec;
            }
        }
    } printf("%d\n", sum);
    for (i=0; i<=rec_top; i++) {
        printf("%d ", rec[i]);
    }
	return 0;
}