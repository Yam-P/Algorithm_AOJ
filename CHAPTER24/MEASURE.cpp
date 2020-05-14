#include <iostream>
#include <vector>

using namespace std;

// the concept of Fenwick Tree 

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}

	int sum(int pos) {
		int ret = 0;
		++pos;
		while (pos > 0) {
			ret += tree[pos];	
			pos &= (pos - 1);
		}
		return ret;
	}

	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};

long long countMoves(const vector<int> &A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		long long a = tree.sum(999999);
		long long b = tree.sum(A[i]);
		ret += a - b;
		tree.add(A[i], 1);
	}
	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	vector<int> A = {5, 1, 4, 3, 2};
		

	cout <<	countMoves(A) << "\n";

	return 0;
}
