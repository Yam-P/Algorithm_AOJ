#include <iostream>
#include <vector>

using namespace std;

// NAMING

void getPrefixSuffix(const string &str) {
	int n = str.size();
	int	beg = 1;
	int matched = 0;
	vector<int> pi(n, 0);

	for (int beg = 1; beg < n; ++beg) {
		for (int i = 0; beg + i < n; ++i) {
			if (str[beg + i] != str[i]) 
				break;
			pi[beg + i] = max(pi[beg + i], i + 1);
		}
	}
	return;
}

vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);

	int begin = 1, matched = 0;
	while (begin + matched < m) {
		if (N[begin +  matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0)
				++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

int main(int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//getPrefixSuffix("alala");
	getPartialMatch("alalba");

	return 0;
}
