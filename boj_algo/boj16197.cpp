#include <stdio.h>
#include <queue>
using namespace std;
typedef pair<int, int> pii;

int N, M;

int map[22][22];
queue<pii> c1;
queue<pii> c2;
queue<int> cnt;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

bool check(int y, int x) {
    if (x < 1 || y < 1 || x > N || x > M) return false;
    return true;
}

int main(void)
{
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; ++i){
        char tmp[22];
        scanf("%s", tmp);
        for (int j = 1; j <= M; ++j) {
            if(tmp[j-1] == '#') map[i][j] = 1;
            else if(tmp[j-1] == 'o' && c1.empty()){
                c1.push({i, j});
            } 
            else if(tmp[j-1]== 'o') c2.push({ i, j});
        }
    }

    cnt.push(0);
    int ans = 1 << 30;
    while(!cnt.empty()) {
        pii coin1 = c1.front(); c1.pop();
        pii coin2 = c2.front(); c2.pop();
        int cc = cnt.front(); cnt.pop();
        if(check(coin1.first, coin1.second) && check(coin2.first, coin2.second)) continue;
        else if((!check(coin1.first, coin1.second) && check(coin2.first, coin2.second)) || check(coin1.first, coin1.second) && !check(coin2.first, coin2.second)) {
            ans = ans > cc ? cc : ans;
            continue;
        }
        else if(cc >= 10) continue;

        for (int i = 0; i < 4; ++i) {
            int ny1 = coin1.first + dy[i];
            int nx1 = coin1.second + dx[i];
            int ny2 = coin2.first + dy[i];
            int nx2 = coin2.second + dx[i];
            c1.push({ny1, nx1});
            c2.push({ny2, nx2});
            cnt.push(cc + 1);
        }

    }

    if(ans == 1 << 30) printf("%d\n", -1);
    else printf("%d\n", ans);

    return 0;
}