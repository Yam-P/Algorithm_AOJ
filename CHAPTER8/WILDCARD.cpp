#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF (987654321)

string wildCardIn;
string strIn;
int cache[101][101];

#if 0
int matchMemoization(int w, int s) {
    // 앞으로 진행될 w, s에 대한 기록
    // w는 w + 1상태로 들어오기 때문에, 이미 진행했던 cache[w][s]를 통해 중복경우 탈출
    int &ret = cache[w][s];
    if (ret != -1) {
        //cout << "repeated case!" << "\n";
        return ret;
    }
    // wild card와 str의 인덱스 각각으로 생각하기
    while (w < wildCardIn.size() && s < strIn.size() && (wildCardIn[w] == '?' || wildCardIn[w] == strIn[s])) {
        ++w;
        ++s;
    }

    if (w == wildCardIn.size()) return ret = (s == strIn.size());

    if (wildCardIn[w] == '*') {
        for (int skip = 0; skip + s <= strIn.size(); ++skip) {
            if(matchMemoization(w + 1, skip + s)) {
                return ret = 1;
            }
        }
    }
    return ret = 0;
}
#endif

int matchMemoization(int w, int s) {
    int &ret = cache[w][s];
    if (ret != -1) {
        //cout << "repeated case!" << "\n";
        return ret;
    }
    // wild card와 str의 인덱스 각각으로 생각하기
    if (w < wildCardIn.size() && s < strIn.size() && (wildCardIn[w] == '?' || wildCardIn[w] == strIn[s])) {
        matchMemoization(w + 1, s + 1);
    }


    if (w == wildCardIn.size() - 1) return ret = (s == strIn.size() - 1);

    if (wildCardIn[w] == '*') {
        // skip과 비교하는 경우, w + 1과 s를 증가시키며 비교했으므로
        // s를 고정하고 w만 증가시키는 방법 + w는 고정하고, s만 계속 증가시키는 방법
        // W[w]와 S[s+1]을 한칸씩 증가시키면서 비교할지
        if (matchMemoization(w + 1, s) || (s < strIn.size() && matchMemoization(w, s + 1))) {
                return ret = 1;
        }
    }
    return ret = 0;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);

    int C;
    cin >> C;
    FOR (c, C) {
        cin >> wildCardIn;
    
        int N;
        cin >> N;
        vector<string> ans;
        FOR (n, N) {
            cin >> strIn;
            // if (search(wildCardIn, strIn)) {
            //     ans.push_back(strIn);
            // }
            memset(cache, -1, sizeof(cache));
            if (matchMemoization(0, 0))
                ans.push_back(strIn);
        }
        sort(ans.begin(), ans.end());
        FOR (i, ans.size()) {
            cout << ans[i] << "\n";
        }
    }
    
	return 0;
 }


 #if 0
bool search(const string &wildCard, const string &str) {
    bool ok = true;
    int idx = INF;
    // *이 없는데 비교문자가 더 긴 경우 
    // wildCard의 size도 함께 고려해줘야함
    for (int i = 0; i < str.size(); ++i) {
        if (wildCard[i] == '*') {
            idx = i;
            break;
        }
        if (wildCard[i] == '?') continue;
        if (wildCard[i] != str[i]) {
            ok = false;
        }
    }

    for (int skip = idx; skip < str.size(); ++skip) {
        if (wildCard[idx + 1] == '\0') break;
        if (str[skip] == wildCard[idx + 1]) {
            ok = search(wildCard.substr(idx + 1), str.substr(skip));
            break;
        }
        if (skip == str.size() - 1) ok = false;
    }

    return ok;
}

bool match(const string &w, const string &s) {
    // iteration 증가를 위한 변수
    int pos;
    // w의 ? 있는 경우
    while (pos < s.size() && pos < w.size() && ((w[pos] == '?') || (w[pos] == s[pos])))
        ++pos;
    
    // !w 끝에 도달한 경우, s가 끝나지 않으면 false! -> he?p vs helpp
    if (pos == w.size()) return pos == s.size();
    
    // *를 만나는 경우
    if (w[pos] == '*') {
        // skip을 pos부터 시작하면 종료규칙이 번거로워짐..
        for (int skip = 0; pos + skip <= s.size(); ++skip) {
            if (match(w.substr(pos + 1), s.substr(pos + skip)))
                return true;
        }
    }
    return false;
}
 #endif