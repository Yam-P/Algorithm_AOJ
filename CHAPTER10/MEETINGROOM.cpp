#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// MEETINGROOM
int n;
int schedule() {

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	vector<pair<int, int> > week(n);
	vector<pair<int, int> > month(n);
	vector<pair<int, int> > orderWeek(n);
	vector<pair<int, int> > orderMonth(n);
	for (int i = 0; i < N; ++i) {
		cin >> week[i].first >> week[i].second;
		cin >> month[i].first >> month[i].second;	
		orderWeek[i].first = week[i].second;
		orderWeer[i].second = i;
		orderMonth[i].first = month[i].second;
		orderMonth[i].second = i;
	}
	
	return 0;
}
