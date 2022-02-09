#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define INFINITY_NUM 0x7fffffff
struct station {
    char name[30];
    int state;
    int path;   
}station[1024];
int station_top = -1;

struct line {
    int distance;
    int subway;
}line[1024][1024];

FILE* in;

int find(char target_station[]) {
    int i;
    for (i=0; i<=station_top; i++) {
        if (strcmp(target_station, station[i].name) == 0) {
            return i;
        }
    } return -1;
}

int add(struct station tmp_station) {
    ++station_top;
    strcpy(station[station_top].name, tmp_station.name);
    station[station_top].state = tmp_station.state;
    return station_top;
}

int subway_num;

void init() {
    in = fopen("bgstations.txt", "r");
    fscanf(in, "%d", &subway_num);
    int i, j;
    int tmp_subway, tmp_subway_num;
    struct station tmp_station;
    int vi, vj;
    for (i=0; i<subway_num; i++) {
        fscanf(in, "%d%d", &tmp_subway, &tmp_subway_num);
        vi = -1, vj = -1;
        for (j=0; j<tmp_subway_num; j++) {
            fscanf(in, "%s %d", tmp_station.name, &tmp_station.state);
            int tmp_index = find(tmp_station.name);
            if (tmp_index == -1) {
                vj = add(tmp_station);
            } else {
                vj = find(tmp_station.name);
            } if (vi != -1) {
                line[vi][vj].distance = 1;
                line[vj][vi].distance = 1;
                line[vi][vj].subway = tmp_subway;
                line[vj][vi].subway = tmp_subway;
            } vi = vj;
        }
    } for (i=0; i<=station_top; i++) {
        for (j=0; j<=station_top; j++) {
            if (i == j) {
                line[i][j].distance = 0;
                line[i][j].subway = 0;
            } else if (line[i][j].distance == 0) {
                line[i][j].distance = 0x7fffffff;
                line[i][j].subway = -1;
            }
        }
    } for (i=0; i<=station_top; i++) {
        station[i].path = -1;
    }
}

char original_station[30];
char destination_station[30];
int original;
int destination;

int path[1024];
int collected[1024];

// void visit(int current_station) {
//     int i;
//     for (i=0; i<=station_top; i++) {
//         if (i == current_station || collected[i] == 1) {
//             continue;
//         } else if (line[current_station][i].distance == 1) {
//             path[i] = current_station;
//             collected[i] = 1;
//             visit(i);
//         }
//     }
// }

int q[1024];
int head = 0, rear = 0;
void visit(int current_station) {
    collected[current_station] = 1;
    q[rear++] = current_station;
    while (head != rear) {
        int tmp_station = q[head++];
        int i;
        for (i=0; i<=station_top; i++) {
            if (line[tmp_station][i].distance == 1 && collected[i] == 0) {
                collected[i] = 1;
                path[i] = tmp_station;
                q[rear++] = i;
            }
        }
    }
}
int res[1024];
int res_top = -1;
void reverse(int res[], int res_top) {
    int i, j;
    for (i=0, j=res_top; i<j; i++, j--) {
        int tmp = res[i];
        res[i] = res[j];
        res[j] = tmp;
    }
}

void print() {
    int cnt = 0;
    int i;
    int current_subway = line[res[0]][res[1]].subway;
    int current_station = res[0];
    for (i=0; i<res_top; i++) {
        if (line[res[i]][res[i+1]].subway != current_subway) {
            printf("%s-%d(%d)-", station[current_station].name, current_subway, cnt);
            current_subway = line[res[i]][res[i+1]].subway;
            current_station = res[i];
            cnt = 0;
        } cnt++;
    } printf("%s-%d(%d)-%s", station[current_station].name, current_subway, cnt, station[res[res_top]].name);
}

int main() {
    init();
    scanf("%s%s", original_station, destination_station);
    original = find(original_station);
    destination = find(destination_station);
    path[original] = -1;
    visit(original);
    int current_station = destination;
    res[++res_top] = destination;
    while (path[current_station] != -1) {
        res[++res_top] = path[current_station];
        current_station = path[current_station];
    } reverse(res, res_top);
    print();
    return 0;
}