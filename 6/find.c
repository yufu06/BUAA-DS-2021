#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define NHASH  3001
#define MULT  37
unsigned int hash(char *str) {
    unsigned int h=0;
    char *p;
    for(p=str; *p!='\0'; p++) {
        h = MULT*h + *p;
    } return h % NHASH;
}
char dictionary[4000][20];
char line[1024];
char word[20];
int rec[30];
struct hash_table {
    int flag;
    char word[20][20];
}hash_rec[3010];
int main () {
    FILE *in;
    in = fopen("dictionary3000.txt", "r");
    int top = -1;
    int rec_top = -1;
    int type;
    int res = 0;
    int i, j;
    scanf("%s%d", word, &type);
    while (fgets(line, 1024, in) != NULL) {
        ++top;
        rec[line[0] - 'a']++;
        sscanf(line, "%s", dictionary[top]);
        memset(line, 0, sizeof (line));
        int index = hash(dictionary[top]);
        hash_rec[index].flag++;
        strcpy(hash_rec[index].word[hash_rec[index].flag-1], dictionary[top]);
    } if (type == 1) {
        int cnt = 0;
        for (i=0; i<=top; i++) {
            cnt++;
            if (strcmp(word, dictionary[i]) == 0) {
                printf("1 %d", cnt);
                return 0;
            } else if (strcmp(word, dictionary[i]) < 0) {
                printf("0 %d", cnt);
                return 0;
            }
        } printf("0 %d", cnt);
    } else if (type == 2) {
        int head = 0;
        int rear = top;
        int mid;
        int cnt = 0;
        while (head <= rear) {
            cnt++;
            mid = (head + rear) / 2;
            if (strcmp(word, dictionary[mid]) == 0) {
                printf("1 %d", cnt);
                return 0;
            } else if (strcmp(word, dictionary[mid]) < 0) {
                rear = mid-1;
            } else {
                head = mid+1;
            }
        } printf("0 %d", cnt);
        return 0;
    } else if (type == 3) {
        int head = 0;
        int rear;
        for (i=0; i<(word[0] - 'a'); i++) {
            head += rec[i];
        } rear = head + rec[i] - 1;
        int mid;
        int cnt = 0;
        while (head <= rear) {
            cnt++;
            mid = (head + rear) / 2;
            if (strcmp(word, dictionary[mid]) == 0) {
                printf("1 %d", cnt);
                return 0;
            } else if (strcmp(word, dictionary[mid]) < 0) {
                rear = mid-1;
            } else {
                head = mid+1;
            }
        } printf("0 %d", cnt);
        return 0;
    } else if (type == 4) {
        int cnt = 0;
        int index = hash(word);
        for (j=hash_rec[index].flag-1; j>0; j--) {
            for (i=0; i<j; i++) {
                if (strcmp(hash_rec[index].word[i], hash_rec[index].word[i+1]) > 0) {
                    char tmp_word[20] = "";
                    strcpy(tmp_word, hash_rec[index].word[i]);
                    memset(hash_rec[index].word[i], 0, sizeof (hash_rec[index].word[i]));
                    strcpy(hash_rec[index].word[i], hash_rec[index].word[i+1]);
                    memset(hash_rec[index].word[i+1], 0, sizeof (hash_rec[index].word[i+1]));
                    strcpy(hash_rec[index].word[i+1], tmp_word);
                }
            }
        } for (i=0; i<hash_rec[index].flag; i++) {
            cnt++;
            if (strcmp(word, hash_rec[index].word) == 0) {
                printf("1 %d", cnt);
                return 0;
            } else if (strcmp(word, hash_rec[index].word) < 0) {
                printf("0 %d", cnt);
                return 0;
            }
        } printf("0 %d", cnt);
    }
	return 0;
}