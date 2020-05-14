#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF (987654321)
#define MAX_SIZE (101)

int n;
int triangle[MAX_SIZE][MAX_SIZE];
int cache[MAX_SIZE][MAX_SIZE];

// 완전탐색
int path(int y, int x, int sum) {
    if (y == n - 1) return triangle[y][x] + sum;
    return max(path(y + 1, x, triangle[y][x] + sum), path(y + 1, x + 1, triangle[y][x] + sum));
}

// 동적 계획법
int path2(int y, int x) {
    if (y == n - 1) return triangle[y][x];
    int &ret = cache[y][x];
    if (ret != -1) return ret;
    // 내려가기 직전 인덱스에 내려간 다음 값을 써놓는 방식.
    // 재귀를 마치고 올라가는 경우, 이 값을 다시 사용할 수 있음.
    return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + triangle[y][x];
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int C;
    cin >> C;

    FOR(c, C) {
        cin >> n;
        FOR(i, n) {
            memset(cache, -1, sizeof(cache));
            for(int j = 0; j <= i; ++j) {
                cin >> triangle[i][j];
            }
        }

        //cout << path(0, 0, 0) << "\n";
        cout << path2(0, 0) << "\n";
    }
    

    
	return 0;
 }
