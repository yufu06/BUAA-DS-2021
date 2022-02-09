#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

int a[25][25]; 

int main() {
	int i, j;
	for (i=1; i<20; i++) {
		for (j=1; j<20; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	// 遍历行
	for (i=1; i<=19; i++) {
		for (j=1; j<=16; j++) {
			if (a[i][j] != 0 && a[i][j+1] == a[i][j] && a[i][j+2] == a[i][j] && a[i][j+3] == a[i][j] && ((j-1 != 0 && a[i][j-1] == 0) || (j+4 != 20 && a[i][j+4] == 0))) {
				printf("%d:%d,%d\n", a[i][j], i, j);
				return 0;
			}
		}
	}
	// 遍历列
	for (i=1; i<=16; i++) {
		for (j=1; j<=19; j++) {
			if (a[i][j] != 0 && a[i+1][j] == a[i][j] && a[i+2][j] == a[i][j] && a[i+3][j] == a[i][j] && ((i-1 != 0 && a[i-1][j] == 0) || (i+4 != 20 && a[i+4][j] == 0))) {
				printf("%d:%d,%d\n", a[i][j], i, j);
				return 0;
			} 
		}
	}
	//遍历右斜线
	for (i=1; i<=16; i++) {
		for (j=1; j<=16; j++) {
			if (a[i][j] != 0 && a[i+1][j+1] == a[i][j] && a[i+2][j+2] == a[i][j] && a[i+3][j+3] == a[i][j] && ((i-1 != 0 && j-1 != 0 && a[i-1][j-1] == 0) || (i+4 != 20 && j+4 != 20 && a[i+4][j+4] == 0))) {
				printf("%d:%d,%d\n", a[i][j], i, j);
				return 0;
			}
		}
	}
	// 遍历左斜线
	for (i=1; i<=16; i++) {
		for (j=4; j<=19; j++) {
			if (a[i][j] != 0 && a[i+1][j-1] == a[i][j] && a[i+2][j-2] == a[i][j] && a[i+3][j-3] == a[i][j] && ((i-1 != 0 && j+1 != 20 && a[i-1][j+1] == 0) || (i+4 != 20 && j-4 != 0 && a[i+4][j-4] == 0))) {
				printf("%d:%d,%d\n", a[i][j], i, j);
				return 0;
			}
		}
	}
	printf("No");
	return 0;
}

