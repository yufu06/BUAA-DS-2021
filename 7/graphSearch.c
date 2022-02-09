#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
struct queue {
    int head;
    int rear;
    int arr[110];
}q;
int visited[110];
int graph[110][110];
void DFS(int v) {
    visited[v] = 1;
    printf("%d ", v);
    int i;
    for (i=0; i<110; i++) {
        if (graph[v][i] == 1 && visited[i] == 0) {
            DFS(i);
        }
    }
}
void BFS(int v) {
    visited[v] = 1;
    printf("%d ", v);
    q.arr[q.rear++] = v;
    while (q.head != q.rear) {
        int tmp_v = q.arr[q.head];
        q.head++;
        int i;
        for (i=0; i<110; i++) {
            if (graph[tmp_v][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                printf("%d ", i);
                q.arr[q.rear++] = i;
            }
        }
    }
}
int main () {
	int nv, ne;
    scanf("%d%d", &nv, &ne);
    int i;
    int vi, vj;
    for (i=0; i<ne; i++) {
        scanf("%d%d", &vi, &vj);
        graph[vi][vj] = 1;
        graph[vj][vi] = 1;
    } int deleted_v;
    scanf("%d", &deleted_v);

    for (i=0; i<110; i++) {
        visited[i] = 0;
    } DFS(0);
    printf("\n");

    for (i=0; i<110; i++) {
        visited[i] = 0;
    } BFS(0);
    printf("\n");

    for (i=0; i<110; i++) {
        graph[deleted_v][i] = 0;
    } for (i=0; i<110; i++) {
        graph[i][deleted_v] = 0;
    } for (i=0; i<110; i++) {
        visited[i] = 0;
    } DFS(0);
    printf("\n");

    for (i=0; i<110; i++) {
        visited[i] = 0;
    } BFS(0);
    
	return 0;
}