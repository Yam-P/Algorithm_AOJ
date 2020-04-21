#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// FENCE using stack

vector<int> h;

int solveStack() {
	stack<int> remaining;
	h.push_back(0);
	int ret = 0;

	for (int i = 0; i < h.size(); ++i) {
		// top 높이가 더 높으면 이 높이로 너비를 바꿔가며 넓이 계산 가능
		while (!remaining.empty() && h[remaining.top()] >= h[i]) {
			int j = remaining.top();
			remaining.pop();
			int width = -1;

			if (remaining.empty()) width = i;
			else width = i - remaining.top() - 1;
			
			ret = max(ret, h[j] * width);
		}
		remaining.push(i);
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int N;
	cin >> N;
	h.resize(N);
	for (int i = 0; i < N; ++i) {
		cin >> h[i];
	}
	cout << solveStack() << "\n";

	return 0;
}