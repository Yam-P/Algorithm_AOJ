#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// MATCHORDER
int N;

#if 0;
int play(vector<int> &russian, vector<int> &korean) {
	vector<bool> selected(N, false);
	int cnt = 0;
	int start = 0;
	for (int i = 0; i < N; ++i) {
		bool nobody = true;
		for (int j = start; j < N; ++j) {
			if (russian[i] <= korean[j] && !selected[j]) {
				selected[j] = true;
				nobody = false;
				cnt++;
				break;
			} 
		}
		if (nobody) {
			selected[start] = true;
			start++;
		} 
	}
	return cnt;
}
#endif

int order(vector<int> &russian, vector<int> &korean) {
	int win = 0;
	for (int rus = 0; rus < russian.size(); ++rus) {
		for (int kor = 0; kor < korean.size(); ++kor) {
			if (korean[kor] < russian[kor]) 
				

		}


	}


}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int C;
	cin >> C;
	while (C-- > 0) {
		cin >> N;
		vector<int> russian(N);
		vector<int> korean(N);
		for (int i = 0; i < N; ++i) cin >> russian[i];	
		for (int i = 0; i < N; ++i) cin >> korean[i];	
		sort(russian.rbegin(), russian.rend());
		sort(korean.begin(), korean.end());

		cout << play(russian, korean) << "\n";
	}	

	return 0;
}

