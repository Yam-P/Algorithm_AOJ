#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF (987654321.0)
int N, L;

double getPrice(vector<double> &cost) {
    double ret = INF;
    for (int i = 0; i < N; ++i) {
        double sum = 0.0;
        for (int j = i; j < N; ++j) {
            sum += cost[j];
            if (j - i + 1 >= L) {
                double avg = sum / (j - i + 1);
                ret = avg < ret ? avg : ret;
            }
        }
    }
    return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    int C;
    cin >> C;
    FOR (c, C) {
        cin >> N >> L;
        vector<double> cost(N); 
        FOR (i, N) {
            cin >> cost[i];
        }
    
        printf("%.12lf\n", getPrice(cost));
    }

	return 0;
 }