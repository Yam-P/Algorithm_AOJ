#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 831p DICTIONARY 
int N;
vector<vector<int> > adj;
vector<int> seen;
vector<int> order;

void makeGraph(const vector<string> &words) {
	adj = vector<vector<int> >(26, vector<int>(26, 0));
	for (int cur = 1; cur < words.size(); ++cur) {
		int prev = cur - 1;
		int len = min(words[cur].size(), words[prev].size());
		for (int k = 0; k < len; ++k) {
			if (words[cur][k] != words[prev][k]) {
				int a = words[prev][k] - 'a';
				int b = words[cur][k] - 'a';
				adj[a][b] = 1;
				break;
			}
		}
	}
}

void dfs(int here) {
	seen[here] = 1;
	for (int next = 0; next < adj[here].size(); ++next) {
		if (!seen[next] && adj[here][next]) {
			dfs(next);
		}
	}
	order.push_back(here);	
}

vector<int> topologicalSort() {
	int m = adj.size();
	seen = vector<int>(m, 0);
	order.clear();

	for (int i = 0; i < m; ++i) {
		if (!seen[i]) dfs(i);
	}
	reverse(order.begin(), order.end());

	for (int i = 0; i < m; ++i) {
		for (int j = i + 1; j < m; ++j) {
			if (adj[order[j]][order[i]])
				return vector<int>();
		}
	}
	return order;	
}


int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	vector<string> words(N);
	for (int i = 0; i < N; ++i) {
		cin >> words[i];
	}

	makeGraph(words);
	vector<int> order = topologicalSort();	
	if (order.empty()) {
		cout << "INVALID HYPOTHESIS" << "\n";
	}
	else {
		for (int i = 0; i < order.size(); ++i) {
			cout << char(order[i] + 'a');
		}
		cout << "\n";
	}
	return 0;
}
