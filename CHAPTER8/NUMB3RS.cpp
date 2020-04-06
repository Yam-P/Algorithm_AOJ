#include <iostream>
#include <vector>

using namespace std;

// NUMB3RS
int n, d, p, q;
int connected[51][51];
int ways[51];
double cache[51][101];

double flee(int here, int days) {
	if (days == d) return (here == q ? 1.0 : 0.0);

	double &ret = cache[here][days];
	if (ret != -1.0) return ret;

	ret = 0.0;
	for (int there = 0; there < n; ++there) {
		if (connected[here][there]) ret += flee(there, days + 1) / ways[here];
	}

	return ret;
}


double flee2(int here, int days) {
	if (days == 0) return (here == p ? 1.0 : 0.0);

	double &ret = cache[here][days];
	if (ret != -1.0) return ret;

	ret = 0.0;
	for (int there = 0; there < n; ++there) {
		if (connected[here][there]) ret += flee2(there, days - 1) / ways[there];
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int C;
	cin >> C;

	for (int c = 0; c < C; ++c) {
		cin >> n >> d >> p;	
		for (int j = 0; j < n; ++j) {
			int sum = 0;
			for (int i = 0; i < n; ++i) {
				cin >> connected[j][i];
				sum += connected[j][i];	
			}
			ways[j] = sum;
		}

		int t;
		cin >> t;

		#if 0	
		for (int i = 0; i < t; ++i) {
			cin >> q;
			// cache initialization
			for (int j = 0; j < 51; ++j) 
				for (int i = 0; i < 101; ++i) 
					cache[j][i] = -1.0;
			printf("%.8lf ", flee(p, 0));	
		}		
		#endif


		// cache initialization
		for (int j = 0; j < 51; ++j) 
			for (int i = 0; i < 101; ++i) 
				cache[j][i] = -1.0;

		for (int i = 0; i < t; ++i) {
			cin >> q;
			printf("%.8lf ", flee2(q, d));	
		}		
		printf("\n");
	}

	return 0;
}
