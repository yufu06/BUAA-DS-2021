#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
char tmp[1024];
char word[200];
struct TreeNode {
	char word[200];
	int cnt;
	struct TreeNode *left;
	struct TreeNode *right;
};
struct TreeNode *buildTree(char *word) {
	struct TreeNode *root = (struct TreeNode *) malloc (sizeof (struct TreeNode));
	strcpy(root->word, word);
	root->cnt = 1;
	root->left = NULL;
	root->right = NULL;
	return root;
}
void insert (struct TreeNode *root, char *word) {
	struct TreeNode *cur = root;
	while (cur != NULL) {
		if (strcmp (word, cur->word) > 0) {
			if (cur->right == NULL) {
				struct TreeNode *newNode;
				newNode = (struct TreeNode *) malloc (sizeof (struct TreeNode));
				strcpy(newNode->word, word);
				newNode->cnt = 1;
				newNode->left = NULL;
				newNode->right = NULL;
				cur->right = newNode;
				break;
			} else {
				cur = cur->right;
			}
		} else if (strcmp(word, cur->word) < 0) {
			if (cur->left == NULL) {
				struct TreeNode *newNode;
				newNode = (struct TreeNode *) malloc (sizeof (struct TreeNode));
				strcpy(newNode->word, word);
				newNode->cnt = 1;
				newNode->left = NULL;
				newNode->right = NULL;
				cur->left = newNode;
				break;
			} else {
				cur = cur->left;
			}
		} else {
			cur->cnt++;
			break;
		}
	}
}
void visit(struct TreeNode *root) {
	if (root == NULL) return;
	visit(root->left);
	printf("%s %d\n", root->word, root->cnt);
	visit(root->right);
} 
int main () {
	FILE *in;
	int i;
	in = fopen("article.txt", "r");
	int pos = -1;
	struct TreeNode *root = NULL;
	int len;
	while (fgets(tmp, 1024, in) != NULL) {
		len = strlen(tmp);
		for (i=0; i<len; i++) {
			if (tmp[i] >= 'A' && tmp[i] <= 'Z') {
				tmp[i] += ('a' - 'A');
			}
		} for (i=0; i<len; i++) {
			if (tmp[i] >= 'a' && tmp[i] <= 'z') {
				word[++pos] = tmp[i];
			} else if (pos != -1) {
				if (root == NULL) {
					root = buildTree(word);
					memset(word, 0, sizeof (word));
					pos = -1;
				} else {
					insert(root, word);
					memset(word, 0, sizeof (word));
					pos = -1;
				}
			} if (i == len-1 && pos != -1) {
				insert(root, word);
				memset(word, 0, sizeof (word));
				pos = -1;
			}
		}
	} struct TreeNode *tmp_root = NULL;
	struct TreeNode *tmp_root_right = NULL;
	struct TreeNode *tmp_root_right_right = NULL;
	if (root != NULL) {
		tmp_root = root;
		if (tmp_root->right != NULL) {
			tmp_root_right = tmp_root->right;
			if (tmp_root->right->right != NULL) {
				tmp_root_right_right = tmp_root->right->right;
			}
		}
	} if (tmp_root != NULL) {
		printf("%s", tmp_root->word);
		if (tmp_root_right != NULL) {
			printf(" %s", tmp_root_right->word);
			if (tmp_root_right_right != NULL) {
				printf(" %s", tmp_root_right_right->word);
			}
		} printf("\n");
	}
	visit (tmp_root);
	fclose(in);
	return 0;
}