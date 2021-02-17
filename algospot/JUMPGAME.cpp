
#include <stdio.h>
#include <string.h>
int N;
int C;

int cache[101][101]; // DP를 저장할 것
int map[101][101]; // 격자를 저장한다.

int jump2(int y, int x)
{
    if (y >= N || x >= N) return 0;
    if (y == N-1 && x == N - 1) return 1;

    int & ret = cache[y][x];
    if (ret != -1) return ret;

    return ret=(jump2(y + map[y][x], x) || jump2(y, x + map[y][x]));
}

int main(void)
{
    scanf("%d", &C);
    for (int tc = 1; tc <= C; ++tc)
    {
        scanf("%d", &N);
        memset(cache, -1, sizeof(cache)); // 초기화
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                scanf("%d", &map[i][j]);
            }
        }

        // DP를 수행한다
        if (jump(0, 0)) printf("YES\n");
        else printf("NO\n");

    }

    return 0;
}
