#include <iostream>
#include <cstring>

using namespace std;
#define FOR(i,n) for(int i = 0; i < n; ++i)

int cache[101][101];
const int MOD = 10000000;

int poly (int n, int first) {
	// return 값은 1이지만, return 후 처리
	if (n == first) return 1;

	int &ret = cache[n][first];
	if (ret != -1) return ret;

	ret = 0;
	for (int second = 1; second <= (n - first); ++second) {
		//printf("case of folding up about next block: %d\n", n - first + second);
		int add = (first + second - 1) * poly(n - first, second);
		add %= MOD;
		ret += add;
		ret %= MOD;
	}
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
		int result = 0;
		for (int first = 1; first <= n; ++first) {
			result += poly(n, first);
			result %= MOD;
		}
		cout << result << "\n";
	}

	return 0;
}
