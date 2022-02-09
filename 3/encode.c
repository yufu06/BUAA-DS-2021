#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct chart {
	char chr;
	struct chart *next;
};

typedef struct chart node;

char rec_a[350];
char rec_b[350];
char res[1300];
char input[2048]; 


int main() {
	gets(rec_a);
	int len = strlen(rec_a);
	int i, j;
	int pos = -1;
	for (i=0; i<len; i++) {
		if (pos == -1 || strchr(rec_b, rec_a[i]) == NULL) {
			rec_b[++pos] = rec_a[i];
		} 
	} len = strlen(rec_b);
	node *tmp = NULL;
	node *head = NULL;
	node *rear = NULL;
	for (i=len-1; i>=0; i--) {
		tmp = (node *)malloc(sizeof(node));
		tmp->chr = rec_b[i];
		if (i == len-1) {
			rear = tmp;
		} tmp->next = head;
		head = tmp;
		tmp = NULL;
	} for (i=32; i<=126; i++) {
		if (strchr(rec_b, i) == NULL) {
			tmp = (node *)malloc(sizeof(node));
			tmp->chr = i;
			rear->next = tmp;
			rear = rear->next;
			tmp = NULL;
		}
	} rear->next = head;
	node* pre = rear;
	int cnt;
	for (i=32; i<=126; i++) {
		cnt = head->chr;
		if (i == 126) {
			res[cnt] = rec_b[0];
			continue;
		} pre->next = head->next;
		head = head->next;
		for (j=1; j<cnt; j++) {
			head = head->next;
			pre = pre->next;
		} res[cnt] = head->chr;
	} FILE *in, *out;
	in = fopen("in.txt", "r");
	out = fopen("in_crpyt.txt", "w");
	while (fgets(input, 2048, in) != NULL) {
		int len_input = strlen(input);
		for (i=0; i<len_input; i++) {
			if (input[i] >= 32 && input[i] <= 126) {
				input[i] = res[input[i]];
			}
		} fputs(input, out);
		fputc('\n', out);
	} fclose(in);
	fclose(out);
	return 0;
}

