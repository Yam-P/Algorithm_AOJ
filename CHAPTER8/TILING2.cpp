#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF (987654321)
#define MAX_SIZE (101)

int n;
int cache[MAX_SIZE];
const int MOD = 1000000007;

int tiling(int w) {
	int &ret = cache[w];
	if (ret != -1) return ret;

	if (w == 1) return 1;
	if (w == 2) return 2;

	return ret = (tiling(w - 1) + tiling(w - 2)) % MOD;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	
	int C;
	cin >> C;

	FOR (c, C) {
		cin >> n;
		memset(cache, -1, sizeof(cache));
		cout << tiling(n) << "\n";      
	}
   
	return 0;
 }
