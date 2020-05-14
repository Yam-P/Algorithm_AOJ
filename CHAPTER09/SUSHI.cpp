#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

// SUSHI
int n, m;
int price[21];
int pref[21];

const int MAX_BUDGET = 2147483647;

#if 0
// 너무커서 완성 시킬수도 없다..
int cache[MAXBUDGET + 1];

int sushi(int budget) {
	int &ret = cache[budget];
	if (ret != -1) {
		//printf("repeated case!\n");
		return ret;
	}
		
	ret = 0;
	for (int dish = 0; dish < n; ++dish) {
		if (budget - price[dish] < 0) continue;
		ret = max(ret, sushi(budget - price[dish]) + pref[dish]);	
	}
	return ret;
}
#endif

#if 0
int c[MAX_BUDGET + 1];
int sushi2() {
	int ret = 0;
	// variable 값으로 넘어왔던 budget을 loop 기준으로 가지고 옴.
	for (int budget = 1; budget <= m; ++budget) {
		c[budget] = 0; // 초기화
		for (int dish = 0; dish < n; ++dish) {
			if (budget < price[dish]) continue;
			c[budget] = max(c[budget], c[budget - price[dish]] + pref[dish]);
		}
		ret = max(ret, c[budget]);
	}
	return ret;
}
#endif

int c[201];
int sushi3() {
	int ret = 0;

	for (int budget = 1; budget <= m; ++budget) {
		c[budget] = 0;
		for (int dish = 0; dish < n; ++dish) {
			if (budget < price[dish]) continue;
			c[budget % 201] = max(c[budget % 201], c[budget % 201 - price[dish]] + pref[dish]);
		}
		ret = max(ret, c[budget]);
	}


}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; ++i) 
		cin >> price[i] >> pref[i];
	
	memset(cache, -1, sizeof(cache));	
	cout << sushi(m) << "\n";

	return 0;
}
