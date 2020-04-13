#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// TICTACTOE
int cache[19683];
bool isFinished(const vector<string> &board, char turn) {
	for (int j = 0; j < 3; ++j) {
		for (int i = 0; i < 3; ++i) {
			if (board[j][i] != turn) break;
			if (i == 2) return true;
		}
	}

	for (int j = 0; j < 3; ++j) {
		for (int i = 0; i < 3; ++i) {
			if (board[i][j] != turn) break;
			if (i == 2) return true;
		}
	}

	for (int i = 0; i < 3; ++i) {
		if (board[i][i] != turn) break;
		if (i == 2) return true;
	}

	for (int i = 0; i < 3; ++i) {
		if (board[2 - i][i] != turn) break;
		if (i == 2) return true;
	}
	
	return false;
}
		

int bijection(const vector<string> &board) {
	int ret = 0;
	for (int j = 0; j < 3; ++j) {
		for (int i = 0; i < 3; ++i) {
			ret *= 3;
			if (board[j][i] == 'o') ret += 1;
			else if (board[j][i] == 'x') ret += 2;
		}
	}
	return ret;
}

int canWin(vector<string> &board, char turn) {
	// 만약 내가 둘 차례인데 상대편이 끝낸 상태라면
	if (isFinished(board, 'o' + 'x' - turn)) return -1;

	int &ret = cache[bijection(board)];
	if (ret != -2) return ret;

	int minVal = 2;
	for (int j = 0; j < 3; ++j) {
		for (int i = 0; i < 3; ++i) {
			if (board[j][i] == '.') {
				board[j][i] = turn;
				minVal = min(minVal, canWin(board, 'o' + 'x' - turn));
				board[j][i] = '.';
			}
		}
	}
	
	if (minVal == 2 || minVal == 0) return ret = 0;

	return ret = -minVal;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int C;
	cin >> C;
	while (C-- > 0) {
		vector<string> board(3);
		int turn = 0;
		for (int j = 0; j < 3; ++j) {
			cin >> board[j];
			for (int i = 0; i < 3; ++i) 
				if (board[j][i] == 'x' || board[j][i] == 'o') turn++;
		}

		char start = turn % 2 ? 'o' : 'x';

		for (int i = 0; i < 19683; ++i) cache[i] = -2; 
		
		int result = canWin(board, start);

		if (result == -1) cout << (char)('x' + 'o' - start) << "\n";
		else if (result ==  1) cout << start << "\n";
		else				   cout << "TIE" << "\n";
	}
	
	return 0;
}