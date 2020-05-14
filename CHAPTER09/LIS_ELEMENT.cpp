#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

// LIS_ELEMENT 최대증가부분 수열 요소 구하기
int N;
int seq[501];
int cache[501 + 1];
int choiced[501 + 1];

// idx 이후로 가장 큰 seq[] 개수를 return
int lis(int cur) {
	int &ret = cache[cur + 1];
	if (ret != -1) {
		//printf("repeated case!\n");
		return ret;	
	}

	ret = 0;
	int bestNext = -1;
	for (int next = cur + 1; next < N; ++next) {
		if (cur == -1 || seq[next] > seq[cur]) {
			if (ret < lis(next) + 1) {
				bestNext = next;	
				ret = lis(next) + 1;
			}
		}
	}
	choiced[cur + 1] = bestNext;
	return ret;
}

int reconstruct(int cur, vector<int> &choicedSeq) {
	// next는 앞에서 선택했던 bestNext이며, seq의 index로 안내해준다.
	if (cur != -1) choicedSeq.push_back(seq[cur]);
	int next = choiced[cur + 1];
	if (next != -1) reconstruct(next, choicedSeq);
}

#if 0
// 여행 짐싸기처럼 하면, 5 6 7 8 1 2 3 4 부분에서 막혀버림..
// lis(idx)가 4 3 2 1 4 3 2 1이 되니깐...
void reconstruct(int idx, vector<int> &picked) {
	if (idx == N) return;

	if (lis(idx) <= lis(idx + 1)) {
		reconstruct(idx + 1, picked);
	}
	else {
		picked.push_back(seq[idx + 1]);
		reconstruct(idx + 1, picked);	
	}
}
#endif

int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	
	for (int i = 0; i < N; ++i) {
		cin >> seq[i];
	}
	memset(cache, -1, sizeof(cache));
	lis(-1);
	vector<int> choicedSeq;
	reconstruct(-1, choicedSeq);


	//vector<int> picked;
	//reconstruct(-1, picked);	

	//for(int i = 0; i < picked.size(); ++i) {
	//	cout << picked[i] << " ";			
	//}
	//cout << "\n";
	return 0;
}
