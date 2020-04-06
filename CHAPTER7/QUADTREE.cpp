#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF (987654321)
#define MAX_SIZE (21)

string code;
int add = 0;
string convert(int &idx) {
    // ** head와 증가분을 나눠서 체크하기
    // ** 증가분은 local이 아닌 global로 설정해서 증가결과를 계속 반영시키기
    int head = idx;
    idx++;

    if (head >= code.size()) return "";
    if (code[head] == 'b' || code[head] == 'w') {
        return string(1, code[head]);
    }

    string part1 = convert(idx);
    string part2 = convert(idx);
    string part3 = convert(idx);
    string part4 = convert(idx);

    // x이후 4개를 바꿔서 반환하는 부분
    return "x" + part3 + part4 + part1 + part2;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int C;
    cin >> C;

    FOR(c, C) {
        cin >> code;
        int idx = 0;
        if (code == "b" || code == "w") cout << code << "\n";
        else cout << convert(idx) << "\n";
    }
    
	return 0;
 }