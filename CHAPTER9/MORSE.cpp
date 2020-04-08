#include <iostream>
#include <cstring>
#include <string.h>

using namespace std;

// MORSE
int n, m;
int skip;
const int MAX_NUM = 1000000000 + 100;

#if 0
void morse(int restN, int restM, string code) {
	// k번째 신호를 이미 출력했으므로 더이상 재귀 필요 없음.
	if (skip < 0) return;

	if (restN == 0 && restM == 0) {
		if (skip == 0) cout << code << "\n";
		--skip;
		return;
	}
	
	if (restN - 1 >= 0) morse(restN - 1, restM, code + "-");
	if (restM - 1 >= 0) morse(restN, restM - 1, code + "o");
}
#endif

int bino[201][201];
void calcBino() {
	memset(bino, 0, sizeof(bino));
	for (int j = 0; j < 200; ++j) {
		bino[j][0] = bino[j][j] = 1;
		for (int i = 1; i < j; ++i) {
			bino[j][i] = bino[j - 1][i] + bino[j - 1][i - 1];	
			bino[j][i] = min(MAX_NUM, bino[j][i]);
		}
	}
}

void morse(int restN, int restM, string code) {
	// k번째 신호를 이미 출력했으므로 더이상 재귀 필요 없음.
	if (skip < 0) return;

	if (restN == 0 && restM == 0) {
		if (skip == 0) cout << code << "\n";
		--skip;
		return;
	}

	// skip을 '-'일 때 만족하면, 0으로 만들고 탈출.
	// 건너 뛰게 되므로 "o"부터 다시 만듦
	if (bino[restN + restM][restN] <= skip) {
		skip -= bino[restN + restM][restN];
		return;
	}
	
	if (restN - 1 >= 0) morse(restN - 1, restM, code + "-");
	if (restM - 1 >= 0) morse(restN, restM - 1, code + "o");
}

string kth(int restN, int restM, int skip) {
	if (restN == 0) return string(restM, 'o');
	
	if (skip < bino[restN + restM - 1][restN - 1]) {
		return "-" + kth(restN - 1, restM, skip);
	}
	return "o" + kth(restN, restM - 1, skip - bino[restN + restM - 1][restN - 1]);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int C;
	cin >> C;
	while (C-- > 0) {
		int k;
		cin >> n >> m >> k;
		skip = k - 1;
		calcBino();
		//morse(n, m, "");
		cout << kth(n, m, skip) << "\n";
	}
	return 0;
}
