#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

// ITES
const int mod = pow(2, 32);
const int MAX_SIZE = 100;
int N;
int A[100];

int generator() {
	A[0] = 1983;
	for (int i = 1; i < N; ++i) {
		A[i] = (A[i - 1] * 214031 + 2531011) % mod;
	}

	return 0;
}

int simple(const vector<int> &signals, int k) {
	int ret = 0;
	for (int head = 0; head < signals.size(); ++head) {
		int sum = 0;
		for (int tail = head; tail < signals.size(); ++tail) {
			sum += signals[tail];
			if (sum == k) ++ret;
			if (sum >= k) break;
		}
	}
	return ret;
}

int optimized(const vector<int> &signals, int k) {
	int rangeSum = 0;
	int tail = 0;	
	int ret = 0;
	for (int head = 0; head < signals.size(); ++head) {
		while (rangeSum < k)
			rangeSum += signals[tail++];
		if (rangeSum == k) ++ret;
		rangeSum -= signals[head];
	}

	return ret;
}

struct RNG {
	unsigned seed;
	RNG() : seed(1983) {}
	unsigned next() {
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret % 10000 + 1;
	}	
};

int countRanges(int k, int n) {
	RNG rng;
	queue<int> ranges;
	int rangeSum = 0;
	int ret = 0;
	for (int i = 0; i < n; ++i) {
		int newSignal = rng.next();
		rangeSum += newSignal;
		ranges.push(newSignal);

		while (rangeSum > k) {
			rangeSum -= ranges.front();
			ranges.pop();
		}

		if (rangeSum == k) ++ret;
	}

}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	N = 5;
	vector<int> test = {1, 4, 2, 1, 4, 3, 1, 6};
	//	cout << simple(test, 7) << "\n";	
	//	cout << optimized(test, 7) << "\n";
	RNG add;
	cout << add.next() << "\n";	
	cout << add.next() << "\n";	
	cout << add.next() << "\n";	
	cout << add.next() << "\n";	
	cout << add.next() << "\n";	
	cout << add.next() << "\n";	
	cout << add.next() << "\n";	
	cout << add.next() << "\n";	

	return 0;
}
