
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;

int C;
int N;
string w;
string s;
string ans[51];
int cache[101][101];
int wsize, ssize;
// 기저 사례에 대해서 이해할 때,
int match(int wpos, int spos)
{
    // *이 마지막에 있고, *은 그대로 wsize - 1인데,
    int & ret = cache[wpos][spos];
    if (ret != -1) return ret;
    if (wpos == wsize && spos == ssize) return 1;
    if((wpos < wsize && spos < ssize)&&(w[wpos] == s[spos] || w[wpos] == '?')) return ret = match(wpos + 1, spos + 1);
    if (w[wpos] == '*')
    {
        // 0번 대응하거나, 다음번 대응하거나 둘 중 하나의 경우밖에 없는 것. 이 경우를 잘못 해석했다.
        if (match(wpos+1, spos) || (spos < ssize && match(wpos, spos + 1)))
        {
            return ret = 1;
        }
    }

    return 0;
}
// *p*
// help
int main(void)
{
    freopen("/Volumes/IMGBND06_smc/TIL/algospot/in.txt", "r", stdin);
    scanf("%d", &C);

    for (int tc = 1; tc <= C; ++tc)
    {
        int ix = 0;
        char temp1[101];
        char temp2[101];
        cin >> w;
        scanf("%d", &N);
        for (wsize = 0; w[wsize]; ++wsize);
        for (int i = 0; i < N; ++i)
        {
            memset(cache, -1, sizeof(cache));
            cin >> s;
            for (ssize = 0; s[ssize]; ++ssize);
            if (match(0, 0))
            {
                ans[ix++] = s;
            }
        }
        sort(ans, ans + ix);
        for (int i = 0; i < ix; ++i) cout << ans[i] <<'\n';

    }

    return 0;
}

