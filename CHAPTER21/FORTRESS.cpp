#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// FORTRESS

struct TreeNode{
	vector<TreeNode*> children;
};

int longest;
int height(TreeNode* root) {
	vector<int> heights;
	for (int i = 0; i < root->children.size(); ++i) {
		heights.push_back(height(root->children[i]));
	}
	if (heights.empty()) return 0;
	sort(heights.begin(), heights.end());

	int hSize = heights.size();
	if (hSize >= 2) 
		longest = max(longest, 2 + heights[hSize - 2] + heights[hSize - 1]);

	return heights[hSize - 1] + 1;
}

int solve(TreeNode* root) {
	longest = 0;
	int h = height(root);
	return max(longest, h);
}

int N;
#define MAX_SIZE 101
int x[MAX_SIZE], y[MAX_SIZE], r[MAX_SIZE];
int sqr(int x) { return x * x; }
int sqrDist(int a, int b) { return sqr(x[b] - x[a]) + sqr(y[b] - y[a]); }

bool encloses(int parent, int child) {
	return (r[parent] > r[child]) && (sqrDist(parent, child) < sqr(r[parent] - r[child]));
}

bool isChild(int parent, int child) {
	if (!encloses(parent, child)) return false;
	
	for (int ch = 0; ch < N; ++ch) {
		if (ch != parent && ch != child && encloses(parent, ch) && encloses(ch, child))
			return false;
	}	
	return true;
}


TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();

	for (int ch = 0; ch < N; ++ch) {
		if(isChild(root, ch)) 
			ret->children.push_back(getTree(ch));
	}
	return ret;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> x[i] >> y[i] >> r[i];
	}

	TreeNode* tree = getTree(0);
	cout << solve(tree) << "\n";
	return 0;
}
