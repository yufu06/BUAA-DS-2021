#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct a {
	int val;
	struct a* next;
};

typedef struct a monkey;

int main() {
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	int i;
	monkey *head = NULL;
	monkey *rear = NULL;
	monkey *pre = NULL;
	monkey *tmp;
	for (i=0; i<n; i++) {
		tmp = (monkey *)malloc(sizeof(monkey));
		tmp->val = n-i; 
		tmp->next = head;
		if (i == 0) {
			rear = tmp;
		} head = tmp;
		tmp = NULL;
	} rear->next = head;
	pre = rear;
	int cnt = 1;
	for (i=1; i<q; i++) {
		head = head->next;
		pre = pre->next;
	} while (head->next != head) {
		if (cnt == m) {
			pre->next = head->next;
			head = head->next;
			cnt = 0;
		} else {
			pre = pre->next;
			head = head->next;
		}
		cnt++;
	} printf("%d", head->val);
	return 0;
}

