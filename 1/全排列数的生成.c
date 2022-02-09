#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

void left(int arr[], int l, int i) {
	int j;
	int tmp = arr[l];
	for (j=l; j<i; j++) {
		arr[j] = arr[j+1];
	} arr[i] = tmp;
}

void right(int arr[], int l, int i) {
	int j;
	int tmp = arr[i];
	for (j=i; j>=l+1; j--) {
		arr[j] = arr[j-1];
	} arr[l] = tmp;
}

void conversion(int arr[], int l, int r) {
	if (l == r) {
		int j;
		for (j=0; j<=r; j++) {
			printf("%d ", arr[j]);
		} printf("\n");
	} else {
		int j;
		for (j=l; j<=r; j++) {
			right(arr, l, j);
			conversion(arr, l+1, r);
			left(arr, l, j);
		}
	}
}

int arr[10];

int main() {
	int n;
	scanf("%d", &n);
	int j;
	for (j=0; j<n; j++) {
		arr[j] = j+1;
	} conversion(arr, 0, n-1);
	return 0;
}

