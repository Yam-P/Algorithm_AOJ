#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)

// 64비트 최솟값을 사용
const long long NEGINF = numeric_limits<long long>::min();

int n, m;
int seqA[100], seqB[100];
int cache[101][101];

int jlis(int idxA, int idxB) {
    //if (idxA == n || idxB == m) return 0;

    int &ret = cache[idxA + 1][idxB + 1];
    if (ret != -1) {
        //cout << "repeated case!\n";
        return ret;
    }

    // ** idx가 -1이면 기준을 가장 낮게 하기
    // 64비트 정수를 사용
    long long refValA = (idxA == -1) ? NEGINF : seqA[idxA];
    long long refValB = (idxB == -1) ? NEGINF : seqB[idxB];
    long long refVal = max(refValA, refValB);

    ret = 2; // seqA, seqB에서 하나 이상씩 고르므로 최소 2
    // idxB는 고정하고 seqA에서 판단하기
    for (int nextA = idxA + 1; nextA < n; ++nextA) {
        if (refVal < seqA[nextA]) {
            ret = max(ret, 1 + jlis(nextA, idxB));
        }
    }

    for (int nextB = idxB + 1; nextB < n; ++nextB) {
        if (refVal < seqB[nextB]) {
            ret = max(ret, 1 + jlis(idxA, nextB));
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
        cin >> n >> m;
        memset(cache, -1, sizeof(cache));
        FOR(i, n) cin >> seqA[i];
        FOR(i, m) cin >> seqB[i];
        cout << jlis(-1, -1) - 2 << "\n"; // 초기 ret = 2이므로
    }

	return 0;
 }