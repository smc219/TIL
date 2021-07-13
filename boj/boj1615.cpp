#include <iostream>
#include <vector>
using namespace std;

int N;
int M;
int ixtree[8010];
vector<int> edge[2020];


void update(int i, int v){
    
}

int search(int s, int e) {
    int sum = 0;
    return sum;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; ++i) {
        int A, B; 
        cin >> A >> B;
        edge[A].push_back(B);
        update(B, 1);
    }

    int ans = 0;

    for (int i = 1; i <= N; ++i) {
        for (int next : edge[i]) {
           ans += search(1, next-1);
           update(next, -1);
        }
    }

    return 0;
}