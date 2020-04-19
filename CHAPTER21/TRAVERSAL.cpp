#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// TRAVERSAL

vector<int> slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a,  v.begin() + b);
}

void printPostOrder(const vector<int>& preOrder, const vector<int>& inOrder) {
	// sub tree의 길이
	const int N = preOrder.size();

	if (preOrder.empty()) return;

	int root = preOrder[0];
	// child L sub tree의 길이
	//vector<int>::iterator 
	int L = find(inOrder.begin(), inOrder.end(), root) - inOrder.begin(); 
	int R = N - 1 - L;

	printPostOrder(slice(preOrder, 1, L + 1), slice(inOrder, 0, L));
	printPostOrder(slice(preOrder, L + 1, N), slice(inOrder, L + 1, N));

	cout << root << " ";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;
	cin >> N;

	vector<int> preOrder(N);
	vector<int> inOrder(N);

	for (int i = 0; i < N; ++i) {
		cin >> preOrder[i]; 
	}
	for (int i = 0; i < N; ++i) {
		cin >> inOrder[i]; 
	}
	
	printPostOrder(preOrder, inOrder);
	cout << "\n";

	return 0;
}
