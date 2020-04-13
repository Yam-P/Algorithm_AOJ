#include <iostream>
#include <cstring>

using namespace std;

// NUMBERGAME 

const int INF = 987654321;
int n;
int board[51];
int cache[51][51];

int play(int left, int right) {
	if (left > right) return 0;

	int &ret = cache[left][right];
	if (ret != -INF) {
		//printf("repeated case!\n");
		return ret;
	}

	ret = board[left] - play(left + 1, right);
	ret = max(ret, board[right] - play(left, right - 1));

	// 두개 이상의 숫자가 있을 경우
	// 0을 고르고 두칸 지운 것과 마찬가지
	if (right - left + 1 >= 2) {
		ret = max(ret, 0 - play(left + 2, right));
		ret = max(ret, 0 - play(left, right - 2));
	}

	return ret;	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int C;
	cin >> C;
	while (C-- > 0) {
		cin >> n;
		for (int i = 0; i < n; ++i) cin >> board[i];
	
		for (int j = 0; j < 51; ++j) {
			for (int i = 0; i < 51; ++i) {
				cache[j][i] = -INF;
			}
		}
		cout << play(0, n - 1) << "\n";
	}
	
	return 0;
}