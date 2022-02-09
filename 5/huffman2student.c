//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32
char tmp[1024];
struct tnode {					//Huffman树结构
	char c;		
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;						//实验步骤 
FILE *Src, *Obj;
	
void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();					//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();					//输出步骤3的结果
void print4();					//输出步骤4的结果


int main()
{
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//输入当前实验步骤 
	
	statCount();						//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1) ? print1(): 1; 			//输出实验步骤1结果	
	createHTree();						//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2) ? print2(Root): 2; 		//输出实验步骤2结果	
	makeHCode(Root);					//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3) ? print3(): 3; 			//输出实验步骤3结果
	(Step>=4) ? atoHZIP(),print4(): 4; 	//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//【实验步骤1】开始 

void statCount()
{
	while (fgets(tmp, 1024, Src) != NULL) {
		int len = strlen(tmp);
		int i;
		for (i=0; i<len; i++) {
			Ccount[tmp[i]]++;
		}
	} Ccount[0] = 1;	
}

//【实验步骤1】结束

//【实验步骤2】开始

void createHTree()
{
	struct tnode *s[130];
	int pos = -1;
	int i, j;
	for (i=0; i<128; i++) {
		if (Ccount[i] == 0) continue;
		struct tnode *p = (struct tnode *) malloc (sizeof (struct tnode));
		p->c = i;
		p->weight = Ccount[i];
		p->left = NULL;
		p->right = NULL;
		s[++pos] = p;
	} int remain = pos;
	while (pos != 0) {
		for (j=pos; j>0; j--) {
			for (i=0; i<j; i++) {
				if (s[i]->weight > s[i+1]->weight) {
					struct tnode *tmpNode = s[i];
					s[i] = s[i+1];
					s[i+1] = tmpNode;
				}
			}
		} struct tnode *p = (struct tnode *) malloc (sizeof (struct tnode));
		p->left = s[0];
		p->right = s[1];
		p->weight = p->left->weight + p->right->weight;
		s[pos+1] = p;
		s[0] = NULL;
		s[1] = NULL;
		for (i=0; i<pos; i++) {
			s[i] = s[i+2];
		} s[pos] = NULL;
		s[pos+1] = NULL;
		pos--;
	} Root = s[0];
}

//【实验步骤2】结束

//【实验步骤3】开始

void visit(struct tnode *root, char c, char *code, int pos) {
	char *tmp_code = (char *) malloc (sizeof (char) * 20);
	strcpy(tmp_code, code);
	tmp_code[++pos] = c;
	if (root->left == NULL && root->right == NULL) {
		tmp_code[++pos] = 0;
		strcpy(HCode[root->c], tmp_code);
	} else {
		visit(root->left, '0', tmp_code, pos);
		visit(root->right, '1', tmp_code, pos);
	}
}

void makeHCode()
{
	int pos = -1;
	visit(Root->left, '0', "", pos);
	visit(Root->right, '1', "", pos);
}

//【实验步骤3】结束

//【实验步骤4】开始
char rec[20480];
void atoHZIP()
{
	Src=fopen("input.txt","r");
	int i, j;
	char line[1024] = "";
	while (fgets(line, 1024, Src) != NULL) {
		int len = strlen(line);
		for (i=0; i<len; i++) {
			strcat(rec, HCode[line[i]]);
		}
	} strcat(rec, HCode[0]);
	int num = 0;
	int index = 7;
	for (i=0; rec[i]!=0; i++) {
		int tmp_num = 1;
		for (j=0; j<index; j++) {
			tmp_num *= 2;
		} num += (rec[i]-'0') * tmp_num;
		index--;
		if ((i+1)%8 == 0) {
			fputc(num, Obj);
			printf("%x", num);
			num = 0;
			index = 7;
		}
	} if (num != 0) {
		fputc(num, Obj);
		printf("%x", num);
		num = 0;
		index = 7;
	}
}

//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
