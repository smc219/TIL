#include <iostream>
#define ABS(a) ((a) > 0 ? (a) : -(a))
using namespace std;

int C;
int P;
int kan[110];

int check1(int s){
    int cnt = 1;
    if (s + 3 <= C) {
        if (kan[s] == kan[s+1] == kan[s+2] == kan[s+3]) cnt++;
    }
    return cnt;
}

int check2(int s) {
    if (s + 1 <= C && kan[s] == kan[s+1]) return 1;
    else return 0;
}

int check34(int s) {
    int cnt = 0;
    if (s + 1 <= C) {
        if(kan[s] - kan[s+1] == 1) cnt++;
        else if(kan[s+1] - kan[s]) cnt++;
    }
    if (s + 2 <= C) {
        if (kan[s] == kan[s+1] == kan[s+2] -1) cnt++;
        else if (kan[s] -1 == kan[s+1] == kan[s+2]) cnt++;
    }
    return cnt;
}

int check5(int s) {
    int cnt = 0;
    if (s + 2 <= C && (kan[s] == kan[s+1] == kan[s+2])) cnt++;
    if (s + 2 <= C && (kan[s] == kan[s+1] + 1 == kan[s+2])) cnt++;
    if (s + 1 <= C && (ABS(kan[s] - kan[s+1]) == 1)) cnt++;
    return cnt;
}

int check67(int s) {
    int cnt = 0;
    if(s + 2 <= C && (kan[s] == kan[s+1] == kan[s+2])) cnt++;
    if(s + 2 <= C && (kan[s] == kan[s+1] -1 == kan[s+2] -1 || kan[s] == kan[s+1] == kan[s+2] + 1)) cnt++;
    
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    return 0;
}