#include <iostream>
#include <vector>

using namespace std;

// the concept of dfs 

vector<vector<int> > adj;
vector<bool> visited;

void dfs(int here) {
	cout << "DFS visits: " << here << "\n";
	visited[here] = true;

	for (int next = 0; next < adj[here].size(); ++next) {
		if (adj[here][next] && !visited[next]) {
			dfs(next);	
		}
	}	
}

void dfsAll() {
	visited = vector<bool>(adj.size(), false);
	for (int next = 0; next < adj.size(); ++next) {
		if (!visited[next]) dfs(next);
	}
}

int dfsCntComp() {
	int ret = 0;	
	visited = vector<bool>(adj.size(), false);
	for (int next = 0; next < adj.size(); ++next) {
		if (!visited[next]) {
			dfs(next);
			++ret;
		}
	}
	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;
	cin >> N;
	
	adj = vector<vector<int> >(N, vector<int>(N, 0));
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < N; ++i) {
			cin >> adj[j][i];	
		}
	}

	//dfsAll();	

	cout << "# of component: \n" << dfsCntComp() << "\n";

	return 0;
}

// dfsAll() input
// 4
// 0 1 0 1
// 1 0 0 0
// 0 0 0 1
// 0 1 1 0
// return: 0 - 1 - 3 - 2

// dfsCntComp() input
// 8
// 0 1 0 0 0 0 1 0
// 1 0 0 0 0 1 0 0
// 0 0 0 1 1 0 0 1
// 0 0 1 0 1 0 0 0
// 0 0 1 1 0 0 0 1
// 0 1 0 0 0 0 0 0
// 1 0 0 0 0 0 0 0
// 0 0 1 0 1 0 0 0
// return: 2



