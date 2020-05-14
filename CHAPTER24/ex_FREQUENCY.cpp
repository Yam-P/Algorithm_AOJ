#include <iostream>
#include <vector>

using namespace std;

// segment tree example. calculation frequency

struct RMQ {
	int n;
	vector<int> freqRange;
	
	RMQ(const vector<int> &array) {
		n = array.size();
		freqRange.resize(n * 4);
		init(array, 0, n - 1, 1);
	} 

	int init(const vector<int> &array, int left, int right, int node) {
		if (left == right) return freqRange[node] = 1;
		
		int mid = (left + right) / 2;
		int leftFreq = init(array, left, mid, node * 2);
		int rightFreq = init(array, mid + 1, right, node * 2 + 1);
		return freqRange[node] = merging(a, b).mostFreq;
	}
};

struct RangeResult {
	int size;
	int mostFreq;

	int leftNum, leftFreq;
	int rightNum, rightFreq;
};

RangeResult merging(const RangeResult &a, const RangeResult &b) {
	RangeResult ret;
	ret.size = a.size + b.size;

	ret.leftNum = a.leftNum;
	ret.leftFreq = a.leftFreq;

	ret.rightNum = b.rightNum;
	ret.rightFreq = b.rightFreq;

	if (a.size == a.leftFreq && a.leftNum == b.leftNum) {
		ret.leftFreq += b.leftFreq;
	}
	
	if (b.size == b.rightFreq && b.rightNum == a.rightNum) {
		ret.rightFreq += a.rightFreq;
	}

	ret.mostFreq = max(a.mostFreq, b.mostFreq);
	if (a.rightNum == b.leftNum) {
		ret.mostFreq = max(ret.mostFreq, a.rightFreq + b.leftFreq);
	}

	return ret;
}

int main (int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	return 0;
}
