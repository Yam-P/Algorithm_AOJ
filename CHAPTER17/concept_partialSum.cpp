/**
*	@file		concept_partialSum.cpp		
*	@manual		1st line: arraySize begin end
				2nd line: arrayElements	
*	@brief		solve partial sum and variance	
*	@reference	
*	@functions	
*
*	@author		yamp
*	@date		Apr 26, 2020
*/

#include <iostream>
#include <vector>

using namespace std;

// the concept of partial sum

vector<int> partialSum(const vector<int> &array) {
	vector<int> ret(array.size());
	ret[0] = array[0];
	for (int i = 1; i < array.size(); ++i) {
		ret[i] = ret[i - 1] + array[i];
	}	
	return ret;
}

vector<int> sqPartialSum(const vector<int> &array) {
	vector<int> ret(array.size());
	ret[0] = array[0] * array[0];
	for (int i = 1; i < array.size(); ++i) {
		ret[i] += ret[i - 1] + array[i] * array[i];
	}
	return ret;
}

int rangeSum(const vector<int> &psum, int a, int b) {
	if (a == 0) return psum[b];
	return psum[b] - psum[a - 1];	
}

double variance(const vector<int> &sqpsum, const vector<int> &psum, int a, int b) {
	double sqpRangeSum = rangeSum(sqpsum, a, b);
	double pRangeSum = rangeSum(psum, a, b); 
	double mean = rangeSum(psum, a, b) / double(b - a + 1);
	
	return  (sqpRangeSum - 2 * mean * pRangeSum + (b - a + 1) * mean * mean) / double(b - a + 1);
}

int main(int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N, a, b;
	cin >> N >> a >> b;
	vector<int> array(N);
	for (int i = 0; i < N; ++i) {
		cin >>	array[i]; 
	}

	vector<int> psum =	partialSum(array);
	vector<int> sqpsum = sqPartialSum(array);
	cout << variance(sqpsum, psum, a, b) << "\n";
	return 0;
}
