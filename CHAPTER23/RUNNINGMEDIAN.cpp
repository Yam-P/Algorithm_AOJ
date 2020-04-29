#include <iostream>
#include <queue>

using namespace std;

struct RNG {
	int seed, a, b;
	// 생성자
	RNG(int _a, int _b) : seed(1983), a(_a), b(_b) {} 
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a + b) % 20090711);
		return ret; 
	}
}; 

int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int> > maxHeap;
	priority_queue<int, vector<int>, greater<int> > minHeap;
	int ret = 0;

	for (int cnt = 1; cnt <= n; ++cnt) {
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
	
		if (!maxHeap.empty() && !minHeap.empty() && maxHeap.top() > minHeap.top()) {
			// root swap
			int a = maxHeap.top();
			int b = minHeap.top();
			maxHeap.pop();
			minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}
		ret  = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N, a, b;
	cin >> N >> a >> b;

	RNG rng(a, b);
	cout << runningMedian(N, rng) << "\n";
	
	return 0;
}
