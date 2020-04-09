#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

// KLIS

int N;
int S[501];
const int MAX = 2000000000 + 1;
int cacheLen[501], cacheCnt[501];

int lis(int cur) {
	int &ret = cacheLen[cur + 1];
	if (ret != -1) return ret;

	// 아래 for문에 들어가지 않을 경우 역시 set에 S[cur]은 들어가므로
	ret = 1;
	for (int next = cur + 1; next < N; ++next) {
		if (cur == -1 || S[cur] < S[next]) {
			ret = max(ret, lis(next) + 1);
		}
	}
	return ret;
}

// count의 return은 조건을 만족 시키는 경우 1
int count(int cur) {
	// 기저사례: lis가 1개인 경우
	if (lis(cur) == 1) return 1;

	int &ret = cacheCnt[cur + 1];
	if (ret != -1) return ret;
	
	ret = 0;
	for (int next = cur + 1; next < N; ++next) {
		// **핵심: 현재 원소부터 시작하는 lis는 다음 원소부터 시작하는 lis보다 한개 많다.
		//        만약 이 둘이 다른 경우, 즉 next 원소부터 시작하는 수열의 lis가 더 적은 경우는 전체 lis를 만들지 못한다.
		if ((cur == -1 || S[cur] < S[next]) && lis(cur) == lis(next) + 1)
			// 조건을 만족시키는 경우 하나씩 더해나가기
			ret = min<long long>(MAX, (long long)ret + count(next));		
	}
	return ret;
}

void reconstruct(int cur, int skip, vector<int> &set) {
	if (cur != -1) set.push_back(S[cur]);
	
	vector<pair<int, int> > followers;
	for (int next = cur + 1; next < N; ++next) {
		if ((cur == -1 || S[cur] < S[next]) && lis(cur) == lis(next) + 1)
			// cur이 -1인 경우, lis를 최대로 만드는 경우가 두가지라면
			// 두 수와 그 인덱스를 넣어놓기.
			followers.push_back(make_pair(S[next], next));
	}

	// lis를 만족시키는 다음 숫자들을 순서대로 sort
	// cur = -1인 경우 {5, 0}->{1, 1}을 {1, 1}->{5,0} 순서로.
	sort(followers.begin(), followers.end());
	
	// followers[i].second 인덱스 이후로 가질 수 있는 lis 수와 skip을 비교
	// skip보다 작으면 그만큼 뛰어 넘기.
	for (int i = 0; i < followers.size(); ++i) {
		int idx = followers[i].second;
		int cnt = count(idx);
		if (cnt <= skip) skip -= cnt;
		// skip 할 수 있는만큼 했다면
		// 와.. 진짜 디버깅 해봐야 안다... 경이로움
		else {
			reconstruct(idx, skip, set);
			break;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);	

	int C;
	cin >> C;
	while (C-- > 0) {
		int K;
		cin >> N >> K;
		for (int i = 0; i < N; ++i) {
			cin >> S[i];
		}
		
		memset(cacheLen, -1, sizeof(cacheLen));
		memset(cacheCnt, -1, sizeof(cacheCnt));
		cout << lis(-1) - 1 << "\n";
		vector<int> set;
		reconstruct(-1, K - 1, set); 

		for (int i = 0; i < set.size(); ++i) {
			cout << set[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}
