#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct chart {
	int ID;
    int type;
    int parentNode;
    int portNum;
    struct chart *childrenNode[8];
}*a[10000], *b[10000];
int path[10000];
char tmp[1024];
int bSize = 0;
void visit (struct chart *root) {
    if (root == NULL) return;
    b[bSize++] = root;
    int k;
    for (k=0; k<8; k++) {
        visit(root->childrenNode[k]);
    }
}
int main () {
    int n, m;
    scanf("%d%d", &n, &m);
    FILE *in = fopen("in.txt", "r");
    int i, j;
    for (i=0; i<1000; i++) {
    	path[i] = -1;
	} i = -1; 
	while (fgets(tmp, 1024, in) != NULL) {
        i++;
        a[i] = (struct chart *) malloc (sizeof (struct chart));
        for (j=0; j<8 ;j++) {
        	a[i]->childrenNode[j] = NULL;
		} sscanf(tmp, "%d%d%d%d", &a[i]->ID, &a[i]->type, &a[i]->parentNode, &a[i]->portNum);
        if (a[i]->parentNode != -1 && a[i]->portNum != -1) { 
            a[a[i]->parentNode]->childrenNode[a[i]->portNum] = a[i];
        } memset(tmp, 0, sizeof (tmp));
    } visit(a[0]);
    int min = 10000;
    int cnt = 10000;
    int sum_cur_a;
    int sum_cur_b;
    int mark = -1;
    int flag;
    struct chart *cur_a, *cur_b;
	for (j=0; j<=i; j++) {
    	if (b[j]->type == 2) {
    		cur_a = a[m];
    		sum_cur_a = 0;
    		flag = 0;
    		while (1) {
    			sum_cur_b = 0;
    			cur_a = a[cur_a->parentNode];
    			sum_cur_a++;
    			cur_b = b[j];
    			while (1) {
    				cur_b = a[cur_b->parentNode];
    				sum_cur_b++;
    				if (cur_b == a[0] && cur_b != cur_a) {
    					break;
					} if (cur_b == cur_a) {
						flag = 1;
						break;
					}
				} if (flag == 1) {
					cnt = sum_cur_a + sum_cur_b;
					if (cnt < min) {
						mark = b[j]->ID;
						min = cnt;
					} break;
				}
			}
		}
	} int tag_i = 0;
	int tag_j = 0;
	int u, v;
	cur_a = a[m];
	cur_b = a[mark];
	for (u=0; cur_a!=a[0]; u++) {
		path[u] = a[cur_a->parentNode]->ID;
		cur_a = a[cur_a->parentNode];
	} for (v=9999; cur_b!=a[0]; v--) {
		path[v] = a[cur_b->parentNode]->ID;
		cur_b = a[cur_b->parentNode];
	} printf("%d", mark);
	flag = 0;
	for (i=0; i<10000; i++) {
		tag_j = 0;
		for (j=9999; j>i; j--) {
			if (path[j] == path[i]) {
				tag_i = i;
				tag_j = j;
				flag = 1;
				break;
			}
		} if (flag == 1) {
			break; 
		}
	} for (i=0; i<tag_i; i++) {
		printf(" %d", path[i]);
	} 
	for (j=tag_j; j<10000; j++) {
		printf(" %d", path[j]);
	}
	return 0;
}
