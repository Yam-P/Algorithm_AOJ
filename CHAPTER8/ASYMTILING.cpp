#include <iostream>
#include <cstring>

using namespace std;

#define FOR(i, n) for(int i = 0; i < n; ++i)
#define MAX_SIZE (101)
#define MOD (1000000007)

int cache[MAX_SIZE];

int cover(int width) {
	if (width <= 1) return 1;

	int &ret = cache[width];
	if (ret != -1) return ret;

	return ret = (cover(width - 2) + cover(width - 1)) % MOD;
}

int findSym(int width) {
	int ret = cover(width);
	if (width % 2 == 1) 
		return (ret - cover(width / 2) + MOD) % MOD;
	
	// 짝수인 경우 - 가운데 대칭인 경우 / 가운데 가로블록 있는 경우
	ret = (ret - cover(width / 2) + MOD) % MOD;
	ret = (ret - cover((width - 2) / 2) + MOD) % MOD; 
	return ret;
} 

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int C;
	cin >> C;
	FOR (c, C) {
		int n;
		cin >> n;

		memset(cache, -1, sizeof(cache));
		cout << findSym(n) << "\n";
	}

	return 0;
}
