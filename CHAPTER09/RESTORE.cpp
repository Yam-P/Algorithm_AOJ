#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// RESTORE
const int INF = 987654321;
int k;
string strIn[16];
int overlap[16][16];
int cache[41][1 << 16];

int overlapCnt(int word1, int word2) {
	string str1 = strIn[word1];
	string str2 = strIn[word2];
	int ret = 0;	
	for (int k = 0; k < str1.size(); ++k) {
		int cnt = 0;
		int i = k;
		int j = 0;
		while (i < str1.size() && j < str2.size()) {
			if (str1[i] == str2[j]) cnt++;
			else break;
			i++;
			j++;
		}
		ret = max(ret, cnt);
	}
	return ret;
}

void preCalc() {
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < k; ++j) {
			if (i != j) overlap[i][j] = overlapCnt(i, j);
		}
	} 
}

int used;
int restore(int cur, int used) {
	if (used == (1 << k) -1) return 0;
	
	int &ret = cache[cur][used];
	if (ret != -1) {
		printf("repeated case!\n");
		return ret;
	}

	ret = 0;	
	for (int next = 0; next < k; ++next) {
		if (used & (1 << next)) continue; 	
		int cand = overlap[cur][next] + restore(next, used | (1 << next));	
		ret = max(ret, cand);  // 겹치는 부분이 많을 수록 짧은 문자열 
	}

	return ret;
}

string reconstruct(int cur, int used) {
	if (used == (1 << k) - 1) return "";
	
	for (int next = 0; next < k; ++next) {
		// 방문 되었던 애면
		if (used & (1 << next)) continue;
		int ifUsed = restore(next, used | (1 << next)) + overlap[cur][next];
		if (restore(cur, used) == ifUsed)
			return (strIn[next].substr(overlap[cur][next]) + reconstruct(next, used | (1 << next)));
	}

	return "****oops****";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> k;
	for (int i = 0; i < k; ++i) {
		cin >> strIn[i];
	}
	strIn[k] = "";
	preCalc();
	memset(cache, -1, sizeof(cache));
	//cout << restore(k, 0) << "\n";
	cout << reconstruct(k, 0) << "\n";

	return 0;
}
