#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF (987654321)
int n, m;
vector<pair<int, int> > couple;

int getSize(int mask) {
    if (mask == 0) return 0;
    return mask % 2 + getSize(mask / 2);
}

int matching(int idx, int choiced) {
    // n명이 모두 찼다면
    if (getSize(choiced) == n) {
        return 1;
    }
    if (idx == m) {
        return 0;
    }

    int ret = 0;
    for (int i = idx; i < m; ++i) {
        // 만약, 이미 선택된 학생이면 건너뛰기
        int occupied = 1 << couple[i].first | 1 << couple[i].second;
        if ((choiced & occupied) != 0) continue; 
        choiced |= occupied;
        ret += matching(i + 1, choiced);
        choiced &= ~occupied;
    }
    return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    int C;
    cin >> C;
    FOR(c, C) {
        cin >> n >> m;

        couple.resize(m);
        FOR(i, m) {
            cin >> couple[i].first >> couple[i].second;
        }

        cout << matching(0, 0) << "\n";
    }
    
	return 0;
 }