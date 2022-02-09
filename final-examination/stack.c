#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct chart {
    char name[50];
    int functionUse[20];
    int functionUseTop;
}function[1000];
int functionTop = -1;
int stack[300];
int stackTop = -1;
int option;
char tmpFunctionName[50];

int main () {
	scanf("%d", &option);
    int i, j;
    for (i=0; i<1000; i++) {
        function[i].functionUseTop = -1;
    } if (option == 5) {
        scanf("%s", function[++functionTop].name);
        stack[++stackTop] = functionTop;
    } while (stackTop != -1) {
        scanf("%d", &option);
        if (option == 0) {
            stack[stackTop--] = 0;
        } else if (option == 5) {
            scanf("%s", tmpFunctionName);
            int flag = 0;
            for (i=0; i<=functionTop; i++) {
                if (strcmp(tmpFunctionName, function[i].name) == 0) {
                    flag = 1;
                    break;
                }
            } if (flag == 0) {
                ++functionTop;
                strcpy(function[functionTop].name, tmpFunctionName);
                stack[++stackTop] = functionTop;
            } else if (flag = 1) {
                stack[++stackTop] = i;
            } int tmpIndex = stack[stackTop-1];
            flag = 0;
            for (i=0; i<=function[tmpIndex].functionUseTop; i++) {
                if (function[tmpIndex].functionUse[i] == stack[stackTop]) {
                    flag = 1;
                    break;
                }
            } if (flag == 0) {
                function[tmpIndex].functionUse[++function[tmpIndex].functionUseTop] = stack[stackTop];
            }
        }
    } for (i=0; i<=functionTop; i++) {
        if (function[i].functionUseTop != -1) {
            printf("%s:", function[i].name);
            for (j=0; j<=function[i].functionUseTop; j++) {
                printf("%s", function[function[i].functionUse[j]].name);
                if (j != function[i].functionUseTop) {
                    printf(";");
                } else printf("\n");
            }
        }
    }
	return 0;
}