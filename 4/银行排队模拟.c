#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
int rec[1000];
int num[1000];
int main() {
	int pre = 0;
	int aft = 0;
	int n;
	scanf("%d", &n);
	int i, j;
	for (i=0; i<n; i++) {
		scanf("%d", &num[i]);
	} i = 0;
	int nowOpen = 3;
	while (aft > pre || i < n) {
		aft += num[i];
		if ((aft - pre) / nowOpen < 7 && nowOpen > 3) {
			nowOpen--;
		} else if (i < n && (aft - pre) / nowOpen >= 7 && nowOpen < 5) {
			nowOpen++;
		} if (i < n && (aft - pre) / nowOpen >= 7 && nowOpen < 5) {
			nowOpen++;
		} if (aft - pre <= nowOpen) {
			pre = aft;
		} else {
			pre += nowOpen;
		} for (j = pre+1; j <= aft; j++) {
			rec[j]++;
		} i++;
	} for (i = 1; i <= aft; i++) {
		printf("%d : %d\n", i, rec[i]);
	}
	return 0;
}




