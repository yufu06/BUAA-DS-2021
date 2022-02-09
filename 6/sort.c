#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
int a[10000];
void selectSort(int a[], int num) {
    int i, j;
    int min;
    int index;
    int tmp;
    int cnt = 0;
    for (j=0; j<num; j++) {
        for (i=j; i<num; i++) {
            if (i==j) {
                min = a[i];
                index = i;
            } else if ((++cnt) && a[i] < min) {
                min = a[i];
                index = i;
            }
        } tmp = a[j];
        a[j] = a[index];
        a[index] = tmp;
    } for (i=0; i<num; i++) {
        printf("%d ", a[i]);
    } printf("\n%d", cnt);
}

void bubbleSort(int a[], int num) {
    int i, j;
    int cnt = 0;
    int tmp;
    int flag;
    for (j=num-1; j>0; j--) {
        flag = 0;
        for (i=0; i<j; i++) {
            cnt++;
            if (a[i] > a[i+1]) {
                flag = 1;
                tmp = a[i];
                a[i] = a[i+1];
                a[i+1] = tmp;
            }
        } if (flag == 0) {
            break;
        }
    } for (i=0; i<num; i++) {
        printf("%d ", a[i]);
    } printf("\n%d", cnt);
}
int heapSort_cnt;
void adjust(int k[], int i, int n) {
    int j, temp;
    temp = k[i];
    j = 2 * i + 1;
    while (j < n) {
        if (j < n-1 && k[j] < k[j+1]) {
            j++;
        } if ((++heapSort_cnt) && temp >= k[j]) {
            break;
        } k[(j-1)/2] = k[j];
        j = 2 * j + 1;
    } k[(j-1)/2] = temp;
}

void heapSort(int a[], int n) {
    int i;
    int temp;
    for (i=n/2-1; i>=0; i--) {
        adjust(a, i, n);
    } for (i=n-1; i>=1; i--) {
        temp = a[i];
        a[i] = a[0];
        a[0] = temp;
        adjust(a, 0, i);
    } for (i=0; i<n; i++) {
        printf("%d ", a[i]);
    } printf("\n%d", heapSort_cnt);
}

int mergeSort_cnt;
void merge(int x[], int tmp[], int left, int leftend, int rightend) {
    int i = left, j = leftend + 1, q = left;
    while (i <= leftend && j <= rightend) {
        if ((++mergeSort_cnt) && x[i] <= x[j]) {
            tmp[q++] = x[i++];
        } else {
            tmp[q++] = x[j++];
        } 
    } while (i <= leftend) {
            tmp[q++] = x[i++];
        } while (j <= rightend) {
            tmp[q++] = x[j++];
        } for (i = left; i<=rightend; i++) {
            x[i] = tmp[i];
    }
}

void mSort(int k[], int tmp[], int left, int right) {
    int center;
    if (left < right) {
        center = (left + right) / 2;
        mSort(k, tmp, left, center);
        mSort(k, tmp, center+1, right);
        merge(k, tmp, left, center, right);
    }
}

void mergeSort(int k[], int n) {
    int *tmp = (int *) malloc (sizeof (int) * n);
    if (tmp != NULL) {
        mSort(k, tmp, 0, n-1);
        free(tmp);
    } int i;
    for (i=0; i<n; i++) {
        printf("%d ", a[i]);
    } printf("\n%d", mergeSort_cnt);
}

int quickSort_cnt;
void quickSort(int k[], int left, int right) {
    int i, last;
    if (left < right) {
        last = left;
        for (i = left + 1; i <= right; i++) {
            if ((++quickSort_cnt) && k[i] < k[left]) {
                ++last;
                int tmp = k[last];
                k[last] = k[i];
                k[i] = tmp;
            }
        } int tmp = k[left];
        k[left] = k[last];
        k[last] = tmp;
        quickSort(k, left, last-1);
        quickSort(k, last+1, right);
    }
}

int main () {
	int num, type;
    scanf("%d%d", &num, &type);
    int i;
    for (i=0; i<num; i++) {
        scanf("%d", &a[i]);
    } if (type == 1) {
        selectSort(a, num);
    } else if (type == 2) {
        bubbleSort(a, num);
    } else if (type ==3) {
        heapSort_cnt = 0;
        heapSort(a, num);
    } else if (type == 4) {
        mergeSort_cnt = 0;
        mergeSort(a, num);
    } else if (type == 5) {
        quickSort_cnt = 0;
        quickSort(a, 0, num-1);
        int i;
        for (i=0; i<num; i++) {
            printf("%d ", a[i]);
        } printf("\n%d", quickSort_cnt);
    }


	return 0;
}