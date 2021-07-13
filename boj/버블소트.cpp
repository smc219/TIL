#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> A;
vector<int> sortA;

int main(void) {
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        int tmp;
        cin >> tmp;
        A.push_back(tmp);
    }
    sortA = A;
    sort(sortA.begin(), sortA.end());
    for (int next : sortA) cout << next << endl;
    for (int next : A) cout << next << endl;
    return 0;s
}