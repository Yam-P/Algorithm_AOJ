#include <iostream>
#include <vector>

using namespace std;

// CHRISTMAS

vector<int> partialSum(const vector<int> &array, int K) {
	vector<int> ret(array.size());
	ret[0] = 0;
	ret[1] = array[1] % K;
	for (int i = 1; i <= array.size(); ++i) {
		ret[i] = (ret[i - 1] + array[i]) % K;
	}
	return ret;
}

int rangeSum(const vector<int> &psum, int a, int b) {
	if (a < 0) { exit(-1); }
	if (a == 0) return psum[0];
	return psum[b] - psum[a - 1];
}

int waysToBuy(const vector<int> &psum, int k) {
	const int MOD = 20091101;
	vector<long long> count(k, 0);
	for (int i = 0; i < psum.size(); ++i) {
		count[psum[i]]++;
	}
	
	int ret = 0;
	for (int i = 0; count.size(); ++i) {
		if (count[i] >= 2) {
			ret = (ret + count[i] * (count[i] - 1) / 2) % MOD;
		}
	}
	return ret;
}

int main(int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N, K;
	cin >> N >> K;	
	vector<int> box(N);
	for (int i = 1; i <= N; ++i) {
		cin >> box[i]; 
	}

	partialSum(box, K);
	
	

	return 0;
}
