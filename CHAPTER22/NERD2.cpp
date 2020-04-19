#include <iostream>
#include <map>
#include <algorithm>

using namespace std;
int N;

// NERD2
map<int, int> coords;

// 지배당하면 true, 당하지 않으면 false return
bool isDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
	if (it == coords.end()) return false;
	
	return y < it->second;
}

// 일단, x, y는 지배 당하지 않는 애로 구성되어 있을 것.
// isDominated가 true인 애들로
void removeDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);

	// 제거할 애 없음
	if (it == coords.begin()) return;
	it--;


	while(true) {
		if (it->second > y) break;
		
		if (it == coords.begin()) {
			coords.erase(it);
			break;
		}
		else {
			map<int, int>::iterator jt = it;
			--jt;
			coords.erase(jt);
			it = jt;
		}
	}
}

int registered(int x, int y) {
	if (isDominated(x, y)) return coords.size();
	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> N;
	
	for (int i = 0; i < N; ++i) {
		int x, y;
		cin >> x >> y;
		cout <<	registered(x, y) << "\n";	
	}

	return 0;
}
