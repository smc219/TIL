// 진행중


#include <stdio.h>
#include <vector>
#include <string.h>
#define FLOAT (100000000)
using namespace std;
/*
완전 탐색으로 해당 마을을 찾을 수 있는 경우의 수.
dfs로 그냥 depth를 통해서 다음 마을로 옮겨간다.
옮겨 가는 과정에서 n일 차에 a마을로 갈 확률은 항상 같다.
*/
typedef long long ll;
int c;
int n;
int d;
int p;
int connected[55][55];
int conNum[55];
int cache[101][55];


/*
일단 먼저 완전탐색을 구한다.
가장 처음에 dfs를 돌 때, depth는 1, num은 p로 시작한다.
그 과정에서 계속 돌다가, depth와 num이 맞는 것으로 들어가면 그 값을 프린트하면 되는 것.

역으로 들어가면 된다.
dfs에 넣어줄 것은 d와 n인 것.
그래서 하나씩 줄어들며 더해주면 되는데,
줄어드는 과정에서 뭐가 줄어드냐, 연결 된 애들을 돌면서
날짜가 하나씩 줄어들고
그리고 더해주는 것은 뭘 더해주는가? dfs(d-1, 연결된 숫자.)
근데 참조적 투명성이 보장되고, 기저사례인 1일차의 애들은 다 정해져 있기 때문에
캐시에 저장하는 것이 가능하다.
*/

int dfs(int d, int num)
{
    // p랑 연결돼있고 + 거기에다 d == 1(1일차라면)
    if (d == 1 && connected[p][num]) return (FLOAT / conNum[p]);

    int & ret = cache[d][num];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!connected[num][i]) continue;
        ret += dfs(d-1, i);
    }
}

int main(void)
{
    scanf("%d", &c);
    for (int tc = 1; tc <= c; ++tc)
    {
        memset(cache, -1, sizeof(cache));
        memset(conNum, 0, sizeof(conNum));
        scanf("%d %d %d", &n, &d, &p);
        for (int i = 0; i < n; ++i)
        {
            
            for (int j = 0; j < n; ++j)
            {
                int tmp;
                scanf("%d", &connected[i][j]);
                if (tmp) 
                {
                    conNum[i]++;
                }
            }
        }

        int t;
        scanf("%d", &t);
        for (int i = 0; i < t; ++i) 
        {
            int tmp;
            scanf("%d", &tmp);
            dfs(d, tmp);
        }

    }
    return 0;
}
