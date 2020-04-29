#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// concept of range minimum query

const int INT_MAX = numeric_limits<int>::max();
struct RMQ {
	int n;
	vector<int> rangeMin;
	
	RMQ(const vector<int> &array) {
		n = array.size();	
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}

	int init (const vector<int> &array, int left, int right, int node) {
		if (left == right) {
			return rangeMin[node] = array[left];
		}
		
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);

		return rangeMin[node] = min(leftMin, rightMin);
	}
	
	int query (int left, int right, int node, int nodeLeft, int nodeRight) {
		if (left > nodeRight || right < nodeLeft) return INT_MAX;

		if (left <= nodeLeft && right >= nodeRight) return rangeMin[node];

		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), \
				   query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	int query (int left, int right) {
		return query (left, right, 1, 0, n - 1);
	}

	int update (int index, int newValue, int node, int nodeLeft, int nodeRight) {
		if (index > nodeRight || index < nodeLeft) return rangeMin[node];

		if (nodeLeft == nodeRight) rangeMin[node] = newValue;

		int mid = (nodeLeft + nodeRight) / 2;
		return min(update(index, newValue, node * 2, nodeLeft, mid), \
				   update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	
	}
};

int main(int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	vector<int> array = {1, 2, 1, 2, 3, 1, 2, 3, 4};
	
	RMQ rmq(array);
	rmq.query(2, 3);

	return 0;
}
