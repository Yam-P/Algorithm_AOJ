#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

// Chapter 21. the concept of tree

struct TreeNode {
	string label;
	TreeNode* parent;
	vector<TreeNode*> children;
};

void printLabels(TreeNode* root) {
	cout << root->label << "\n";
	
	for (int i = 0; i < root->children.size(); ++i) {
		printLabels(root->children[i]);
	}
}
#if 0
int height(TreeNode* root) {
	int h = 0;
	for (int i = 0; i < root->children.size(); ++i) {
		h = max(h, 1 + height(root->children[i]));
	}
	return h;
}
#endif

int longest = -1;
int height(TreeNode* root) {
	vector<int> heights;
	for (int i = 0; i < root->children.size(); ++i) {
		heights.push_back(height(root->children[i]));
	}
	if (heights.empty()) return 0;
	sort(heights.begin(), heights.end());

	int hSize = heights.size();
	if (hSize >= 2) 
		longest = max(longest, 2 + heights[hSize - 2] + heights[hSize - 1]));

	return heights[hSize - 1] + 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	TreeNode* root;
	TreeNode* child1;
	TreeNode* child2;

	root = new TreeNode;
	child1 = new TreeNode;
	child2 = new TreeNode;

	root->label = "root";
	child1->label = "child1";
	child2->label = "child2";

	root->children.push_back(child1);
	root->children.push_back(child2);

	printLabels(root);
	height(root);

	delete root;
	delete child1;
	delete child2;
	return 0;
}
