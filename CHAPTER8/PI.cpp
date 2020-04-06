#include <iostream>
#include <vector>
#include <cstring>
#include <string.h>
#include <cmath>
using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF (987654321)

string strIn;
int calWordScore(int beg, int end) {
	string str = strIn.substr(beg, end - beg + 1);

	// end = [beg, beg + 3,4,5]
	int curDif, prevDif;// reference diff value
	bool sameDifFlag = true;
	bool repeatedNumFlag = true;
	for (int idx = 1; idx < str.size(); ++idx) {
		curDif = str[idx] - str[idx - 1];
		if (idx != 1 && prevDif != curDif) {
			sameDifFlag = false;
		}
		if (str[idx] != str[idx%2]) {
			repeatedNumFlag = false;
		}
		prevDif = curDif;
	}
	if 		(sameDifFlag && abs(curDif) == 0) return 1;
	else if (sameDifFlag && abs(curDif) == 1) return 2;
	else if (sameDifFlag) return 5;
	else if (repeatedNumFlag) return 4;
	
	return 10;
}

int cache[10002];
int memoization(int start) {
	//** 끝지점을 볼게 아니라 시작하는 지점이 strIn.size()가 되면 return
	// 어차피 return 0이기 때문에, 답이 바뀔까봐 신경쓸 필요 없음.
	if (start == strIn.size()) return 0;

	int &ret = cache[start];
	if (ret != -1) return ret;

	ret = INF;
	for (int L = 3; L <= 5; ++L) {
		if (start + L <= strIn.size()){
			// 만약 1234면, start=0 / L=4 따라서, 들어가는 수는 0 + 3
			ret = min(ret, calWordScore(start, start + L - 1) + memoization(start + L));
		}		
	}

	return ret;
}

int main () {
	ios_base::sync_with_stdio(false);
    cin.tie(0);

	int C;
	cin >> C;
	FOR(c, C) {
		cin >> strIn;
		//cout << calTotalScore(0) << "\n";
		memset(cache, -1, sizeof(cache));
		cout << memoization(0) << "\n";
	}

	return 0;
}

#if 0
int calTotalScore(int start) {
	if (start >= strIn.size() - 2) return 0;
	int ret = 0;
	int nextStart;
	int prevCost = INF;
	for (int next = 3; next <= 5; ++next) {
		int cost = calWordScore(start, next);
		if (prevCost >= cost) {
			nextStart = start + next;
			prevCost = cost;
		}
	}

	ret = prevCost + calTotalScore(nextStart);
	return ret;
}
#endif
