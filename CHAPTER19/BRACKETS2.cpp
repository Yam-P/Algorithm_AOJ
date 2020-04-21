#include <iostream>
#include <string>
#include <stack>

using namespace std;

// BRACKETS2 using stack

#if 0
bool wellMatched(const string& formula) {
    stack<char> openStack;
    for (int i = 0; i < formula.size(); ++i) {
        if (formula[i] == '(' || formula[i] == '{' || formula[i] == '[') {
            openStack.push(formula[i]);
            continue;
        }
            
        if (!openStack.empty()) {
            char bracket = openStack.top();
            if (bracket == '(' && formula[i] == ')')
                openStack.pop();
            else if (bracket == '{' && formula[i] == '}')
                openStack.pop();
            else if (bracket == '[' && formula[i] == ']')
                openStack.pop();
        }
    }    
    return openStack.empty();
}
#endif

bool wellMatched(const string &formula) {
    const string opening("({["), closing(")}]");
    stack<char> openStack;

    for (int i = 0; i < formula.size(); ++i) {
        if (opening.find(formula[i]) != -1) openStack.push(formula[i]);

        else {
            if (openStack.empty()) return false;
            char bracket = openStack.top();
            if (opening.find(bracket) != closing.find(formula[i])){
                return false;
            }
            openStack.pop();
        }
    }
    return openStack.empty();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string strIn;
    cin >> strIn;

    if (wellMatched(strIn)) cout << "YES" << "\n";
    else cout << "NO" << "\n";

    return 0;
}