#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

typedef pair<int, int> pii;

int N;
int M;

int S, E;
int visit[1010];

vector<pii> dist[1010];
priority_queue<pii, vector<pii>, greater<pii> > pq;
int dijkstra() {
    
    
    visit[S] = 0;
    pq.push({0, S});

    while(!pq.empty()) {
        int cv = pq.top().first;
        int cn = pq.top().second;
        pq.pop();

        if (cn == E) return cv;

        for (pii next : dist[cn]) {
	    if (visit[next.second] != -1 && visit[next.second] > cv + next.first) {
            visit[next.second] = cv + next.first;
            pq.push({cv + next.first, next.second});
        }
        }
    }

    return -1;

}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;
    cin >> M;
    memset(visit, -1, sizeof(visit));
    for (int i = 1; i <= M; ++i) {
        int s, e, v;
        cin >> s >> e >> v;
        dist[s].push_back({v, e});
    }
    
    cin >> S >> E;

   // cout << E << "\n";

    cout << dijkstra() << "\n";
    
    return 0;
}