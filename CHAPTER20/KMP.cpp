#include <iostream>
#include <vector>

using namespace std;

vector<int> naiveSearch(const string& H, const string& N) {
	vector<int> ret;
	for (int begin = 0; begin + N.size() <= H.size(); ++begin) {
		bool match = true;
		for (int j = 0; j < N.size(); ++j) {
			if (H[begin + j] != N[j]) {
				match = false;
				break;
			}
		}
		if (match) ret.push_back(begin);
	}
	return ret; 
}

vector<int> getPartialMatchNaive(const string &N) {
	int m = N.size();
	vector<int> pi(m, 0); // N 길이만큼 pi가 생길 수 있음.
	
	for (int begin = 1; begin < m; ++begin) {
		for (int i = 0; i + begin < m; ++i) {
			if (N[begin + i] != N[i]) break;
			pi[begin + i] = max(pi[begin + i], i + 1);
		}
	}
	return pi;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	string H, N;
	cin >> H >> N;
	//vector<int> res = naiveSearch(H, N);
	//for (int i = 0; i < res.size(); ++i) cout << res[i] << " ";
	//cout << "\n";
	
	getPartialMatchNaive(N);

	return 0;
}
