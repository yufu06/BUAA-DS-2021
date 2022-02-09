#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct ListNode {
    int site;
    int len;
    struct ListNode *next;
}*head, *cur, *pre, *old;
int main () {
	int n;
    scanf("%d", &n);
    int i;
    head = NULL;
    cur = head;
    int tmp_len, tmp_site;
    int remain = n;
    for (i=0; i<n; i++) {
        scanf("%d%d", &tmp_site, &tmp_len);
        if (i == 0) {
            cur = (struct ListNode *) malloc (sizeof (struct ListNode));
            head = cur;
            cur->site = tmp_site;
            cur->len = tmp_len;
            cur->next = NULL;
        } else if (i != n-1) {
            cur->next = (struct ListNode *) malloc (sizeof (struct ListNode));
            cur = cur->next;
            cur->site = tmp_site;
            cur->len = tmp_len;
            cur->next = NULL;
        } else {
            cur->next = (struct ListNdoe *) malloc (sizeof (struct ListNode));
            cur = cur->next;
            cur->site = tmp_site;
            cur->len = tmp_len;
            cur->next = head;
            pre = cur;
            cur = cur->next;
        }
    }
    int request;
    while (1) {
        scanf("%d", &request);
        if (request == -1) {
            break;
        }
        old = cur;
        if (cur->len > request) {
            cur->len -= request;
        } else if (cur->len == request) {
            remain--;
            if (remain != 0) {
                pre->next = cur->next;
                cur = cur->next;
            }
        } else {
            cur = cur->next;
            pre = pre->next;
            while (1) {
                if (cur->len > request) {
                    cur->len -= request;
                    break;
                } else if (cur->len == request) {
                    remain--;
                    if (remain != 0) {
                        pre->next = cur->next;
                        cur = cur->next;
                        break;
                    }
                } else {
                    cur = cur->next;
                    pre = pre->next;
                }
                if (cur == old) {
                    break;
                }
            }
        }
    }
    old = cur;
    if (remain != 0) {
        printf("%d %d\n", cur->site, cur->len);
        cur = cur->next;
        while (cur != old) {
            printf("%d %d\n", cur->site, cur->len);
            cur = cur->next;
        }
    }
	return 0;
}