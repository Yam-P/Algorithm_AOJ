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
int cacheCnt[MAX_SIZE][MAX_SIZE];

int path(int y, int x) {
    if (y >= n || x > y) return 0;
    if (y == n - 1) return triangle[y][x];

    int &ret = cache[y][x];
    if (ret != -1) return ret;

    return ret = max(path(y + 1, x), path(y + 1, x + 1)) + triangle[y][x];
}

int count(int y, int x) {
    if (y == n - 1) return 1;

    int &ret = cacheCnt[y][x];
    if (ret != -1) return ret;

    ret = 0;

    // 오른쪽 아래가 크면 오른쪽 아래의 cnt 값을, 아래가 크면 바로 아래의 cnt 값을 가져다 더하기
    if (path(y + 1, x + 1) >= path(y + 1, x)) ret += count(y + 1, x + 1);
    if (path(y + 1, x + 1) <= path(y + 1, x)) ret += count(y + 1, x);

    return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);

    int C;
    cin >> C;
    FOR (c, C) {
        cin >> n;
        FOR (j, n) FOR (i, j + 1) 
            cin >> triangle[j][i];

        memset(cache, -1, sizeof(cache));
        memset(cacheCnt, -1, sizeof(cacheCnt));
        cout << count(0, 0) << "\n";
    }

	return 0;
 }
