#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 27;
const int MAX_M = 1007;

int n, m;
int a[MAX_N][MAX_M];
int dp[MAX_N][MAX_M];
vector<int> divisor[MAX_M];

int main() {
	for (int i = 1; i < MAX_M; ++i) {
		for (int j = 2 * i; j < MAX_M; j += i) {
			divisor[j].push_back(i);
		}
	}
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &a[i][j]);
			}
		}
		memset(dp, 0, sizeof dp);
		for (int i = 1; i <= m; ++i) {
			for (int j = 0; j  < divisor[i].size(); ++j) {
			//	printf("%d %d\n", i, divisor[i][j]);
				dp[1][i] = dp[1][i - 1];
				dp[1][i] = max(dp[1][i], dp[1][divisor[i][j]]);
			}
			dp[1][i] += a[1][i];
		}
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j]);
				dp[i][j] = max(dp[i][j], dp[i][j - 1]);
				for (int k = 0; k < divisor[j].size(); ++k) {
					dp[i][j] = max(dp[i][j], dp[i][divisor[j][k]]);
				}
				dp[i][j] += a[i][j];
			}
		}
		int ans = dp[n][m];
		printf("%d\n", ans);
	}
	return 0;
}
