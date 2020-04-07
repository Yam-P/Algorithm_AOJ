#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

// PACKING - 여행 짐 싸기
int N;
string list[101];
int volume[101];
int need[101];
int cache[1001][101];

// 절박도를 반환
int pack(int rest, int item) {
	// item을 모두 봤으면 종료
	// item + 1 처리해서 들어오므로 N인 경우가 기저사례
	if (item == N) return 0;

	int &ret = cache[rest][item];
	if (ret != -1) return ret;

	// item 선정하지 않는 경우
	ret = pack(rest, item + 1);
	if (rest - volume[item] >= 0) {
		int pick = pack(rest - volume[item], item + 1) + need[item];
		ret = max(ret, pick);
	} 

	return ret;
}

void reconstruct(int rest, int item, vector<int> &picked) {
	if (item == N) return;

	if (pack(rest, item) == pack(rest, item + 1)) {
		reconstruct(rest, item + 1, picked);
	}	
	else {
		picked.push_back(item);
		reconstruct(rest - volume[item], item + 1, picked);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int C;
	cin >> C;
	for (int c = 0; c < C; ++c) {
		int W;
		cin >> N >> W;
		for (int i = 0; i < N; ++i) {
			cin >> list[i] >> volume[i] >> need[i];	
		}

		memset(cache, -1, sizeof(cache));
		vector<int> picked;

		reconstruct(W, 0, picked);	
		cout << pack(W, 0) << " " << picked.size() << "\n";
		
		for (int i = 0; i < picked.size(); ++i) {
			cout << list[picked[i]] << "\n";
		}
	}
	return 0;
}
