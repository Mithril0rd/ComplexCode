#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_Z = 22;
const int MAX_N = 1007;
const long long INF = -1LL<<61;

int n, m;
int sum[MAX_N], l[MAX_N];
long long dp[MAX_Z][MAX_N];

void solve() {
	for (int i = 1; i < MAX_Z; ++i) {
		for (int j = 0; j < MAX_N; ++j) {
			dp[i][j] = INF;
		}
	}
	 for (int i = 1; i <= n; ++i) {
		for (int j = l[i]; j <= m; ++j) {
			if (dp[i - 1][j - l[i]] != INF) 
			  dp[i][j] = max(dp[i][j], dp[i - 1][j - l[i]] + sum[j] - sum[j - l[i]]);
			if (dp[i][j - 1] != INF) 
			  dp[i][j] = max(dp[i][j], dp[i][j - 1]);
		}
	}
	long long ans = INF;
	for (int i = 1; i <= m; ++i) {
		if (dp[n][i] != INF) 
		  ans = max(ans, dp[n][i]);
	}
	
	printf("%lld\n", ans);
	//printf("%I64d\n", ans);
}

int main() {
	while (1 == scanf("%d", &m)) {
		if (0 == m) break;
		int val = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &l[i]);	
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d", &val);
			sum[i] = sum[i - 1] + val;
		}
		solve();
	}
	return 0;
}
