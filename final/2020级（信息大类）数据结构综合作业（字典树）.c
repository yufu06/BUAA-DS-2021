#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
char tmp_stopword[20];
char tmp_line[1024];
char tmp_article_word[50];

struct Trie {
	struct Trie *children[26];
	int cnt;
	int flag;
};

struct chart {
	int sum;
	char sentence[2048];
}sentences[500000], tmp_chart;

struct Trie *buildTree () {
	struct Trie *obj = (struct Trie *) malloc (sizeof (struct Trie));
	memset(obj->children, 0, sizeof (obj->children));
	obj->cnt = 0;
	obj->flag = 0;
	return obj;
}

void insert (struct Trie *obj, char *word) {
	int i;
	int tmp;
	for (i=0; word[i]; i++) {
		if (word[i] < 'a' || word[i] > 'z') {
			continue;
		} tmp = word[i] - 'a';
		if (obj->children[tmp] == NULL) {
			obj->children[tmp] = buildTree();
		} obj = obj->children[tmp];
	} obj->flag = 1;
	obj->cnt = 1;
}

int search(struct Trie *obj, char *word) {
	int i;
	int tmp;
	for (i=0; word[i]; i++) {
		tmp = word[i] - 'a';
		if (obj->children[tmp] == NULL) {
			return 0;
		} obj = obj->children[tmp];
	} if (obj->flag == 1) {
		return 1;
	} return 0;
}

void add(struct Trie *obj, char *word) {
	int i;
	int tmp;
	for (i=0; word[i]; i++) {
		tmp = word[i] - 'a';
		obj = obj->children[tmp];
	} obj->cnt++; 
}

int returnCnt(struct Trie *obj, char *word) {
	int i;
	int tmp;
	for (i=0; word[i]; i++) {
		tmp = word[i] - 'a';
		obj = obj->children[tmp];
	} return obj->cnt;
}

int compar(const void *a, const void *b) {
	struct chart tmp_a = *(struct chart *)a;
	struct chart tmp_b = *(struct chart *)b;
	if (tmp_a.sum < tmp_b.sum) {
		return 1;
	} else {
		return -1;
	}
}

int main () {
	FILE *in, *out;
	in = fopen("stopwords.txt", "r");
	struct Trie *stopwords = buildTree();
	while (fgets(tmp_stopword, 20, in) != NULL) {
		insert(stopwords, tmp_stopword);
		memset(tmp_stopword, 0, sizeof (tmp_stopword));
	} in = fopen("article.txt", "r");
	struct Trie *article_words = buildTree();
	int i;
	int pos = -1;
	while (fgets(tmp_line, 1024, in) != NULL) {
		for (i=0; tmp_line[i]; i++) {
			if (tmp_line[i] >= 'A' && tmp_line[i] <= 'Z') {
				tmp_article_word[++pos] = tmp_line[i] + ('a' - 'A');
			}
			else if (tmp_line[i] >= 'a' && tmp_line[i] <= 'z') {
				tmp_article_word[++pos] = tmp_line[i];
			} else if (pos != -1) {
				if (search(stopwords, tmp_article_word) == 1) {
					memset(tmp_article_word, 0, sizeof (tmp_article_word));
					pos = -1;
				} else {
					if (search(article_words, tmp_article_word) == 0) {
						insert(article_words, tmp_article_word);
						memset(tmp_article_word, 0, sizeof (tmp_article_word));
						pos = -1;
					} else {
						add(article_words, tmp_article_word);
						memset(tmp_article_word, 0, sizeof (tmp_article_word));
						pos = -1;
					}
				}
			}
		} memset(tmp_line, 0, sizeof (tmp_line));
	} in = fopen("article.txt", "r");
	int sentences_num = 0;
	int sentence_pos = -1;
	while (fgets(tmp_line, 1024, in) != NULL) {
		for (i=0; tmp_line[i]; i++) {
			if ((tmp_line[i] != ' ' && tmp_line[i] != '.') || sentence_pos != -1) {
				sentences[sentences_num].sentence[++sentence_pos] = tmp_line[i];
			} if (tmp_line[i] >= 'A' && tmp_line [i] <= 'Z') {
				tmp_article_word[++pos] = tmp_line[i] + ('a' - 'A');
			} else if (tmp_line[i] >= 'a' && tmp_line[i] <= 'z') {
				tmp_article_word[++pos] = tmp_line[i];
			} else {
				if (pos != -1 && search(stopwords, tmp_article_word) == 0) {
					sentences[sentences_num].sum += returnCnt(article_words, tmp_article_word);
				} memset(tmp_article_word, 0, sizeof (tmp_article_word));
				pos = -1;
				if (sentence_pos != -1 && (tmp_line[i] == '.' || tmp_line[i] == '?' || tmp_line[i] == '!')) {
					sentences_num++;
					sentence_pos = -1;
				}
			}
		} memset(tmp_line, 0, sizeof (tmp_line));
	} 
	qsort(sentences, sentences_num, sizeof (sentences[0]), compar);
	int n;
	scanf("%d", &n);
	for (i=0; i<5; i++) {
		printf("%d %s\n", sentences[i].sum, sentences[i].sentence);
	} out = fopen("results.txt", "w");
	for(i=0; i<n; i++) {
		fprintf(out, "%d %s\n", sentences[i].sum, sentences[i].sentence);
	}
	return 0;
}

