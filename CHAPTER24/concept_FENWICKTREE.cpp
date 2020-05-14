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

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	FenwickTree fwtree(5);
	fwtree.add(0, 5);
	fwtree.add(1, 4);
	fwtree.add(2, 3);
	fwtree.add(3, 4);
	fwtree.add(4, 2);
	
	cout <<	fwtree.sum(2) << "\n";	

	return 0;
}
