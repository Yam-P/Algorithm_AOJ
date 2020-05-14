#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF (987654321)
#define MAX_SIZE (501)

int N;
vector<int> seq;
int cache[MAX_SIZE];
int lis(int idx) {
    if (idx == N) return 0;
    int &ret = cache[idx + 1];
    if (ret != -1) {
        //cout << "repeated case!!\n";
        return ret;
    }

    ret = 1; // 초기값 지정해주기
    int refVal = (idx == -1) ? -INF : seq[idx];
    for (int next = idx + 1; next < N; ++next) {
        if (idx == -1 || refVal < seq[next]) {
            ret = max(ret, 1 + lis(next));
        }
    }
    
    return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int C;
    cin >> C;
    FOR(c, C) {
        cin >> N;
        seq.resize(N);
        memset(cache, -1, sizeof(cache));
        FOR(i, N) {
            cin >> seq[i];
        }

        cout << lis(-1) - 1 << "\n"; // -1 넣을 때도 카운트 되므로
    }
    

	return 0;
 }
