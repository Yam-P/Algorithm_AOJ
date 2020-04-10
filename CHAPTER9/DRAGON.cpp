#include <iostream>
#include <algorithm>
#include <cstring>
#include <string.h>
#include <cassert>

using namespace std;

// DRAGON

int n, p, l;

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";
#if 0
// 완전탐색
string dragon(string &seed, int gen) {
	if (gen == n) return seed;
	string newCurve;
	for (int idx = 0; idx < seed.size(); ++idx) {
		if (seed[idx] == 'X') newCurve += "X+YF";
		else if (seed[idx] == 'Y') newCurve += "FX-Y";
		else newCurve += seed[idx];
	}
	return dragon(newCurve, gen + 1);
}

void curve(const string &seed, int gen) {
	if (gen == 0) {
		cout << seed;
		return;
	}
	
	for (int i = 0; i < seed.size(); ++i) {
		if (seed[i] == 'X') curve(EXPAND_X, gen - 1);		
		else if (seed[i] == 'Y') curve(EXPAND_Y, gen - 1);		
		else cout << seed[i];
	}
}
#endif

const int MAX = 1000000000 + 1;
int len[51];
void preCalc() {
	// 원래 0세대는 2이지만, 사용할 일 없으므로 규칙성 유지하도록
	len[0] = 1;
	for (int i = 1; i <= 50; ++i) {
		len[i] = min(len[i - 1] * 2 + 2, MAX);
	} 
}

char expand(const string& dragonCurve, int gen, int skip) {
	if (gen == 0) {
		// skip >= dragonCurve.size() 인 경우 종료한다.
		assert(skip < dragonCurve.size());
		return dragonCurve[skip];
	}
	
	for (int i = 0; i < dragonCurve.size(); ++i) {
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			if (skip >= len[gen])
				skip -= len[gen];
			else if (dragonCurve[i] == 'X')
				return expand(EXPAND_X, gen - 1, skip);
			else // dragonCurve[i] == 'Y'
				return expand(EXPAND_Y, gen - 1, skip);
		}
		// F, +, -를 만나는 경우, skip을 줄이고 다음 글자를 확인
		else if (skip > 0) --skip;
		// skip이 0인 경우 해당 인덱스 문자 출력.
		else return dragonCurve[i];
	}

	return '#';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int C;
	cin >> C;

	preCalc();
	while (C-- > 0) {
		cin >> n >> p >> l;

		//cout << dragon("FX", 0).substr(p - 1, l) << "\n";
		//curve("FX", n);
		
		for (int i = 0; i < l; ++i) 
			cout << expand("FX", n, p + i - 1);
	
		cout << "\n";
	}
	return 0;
}
