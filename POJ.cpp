#include <cstdio>
#include <cstring>

const int MAX_N = 22;
const int MAX_S = 8007;

int n, m;
int mat[MAX_N][MAX_N];
int dp[MAX_N][MAX_S<<1];
int a[MAX_N], b[MAX_N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%d", b + i);
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			mat[i][j] = b[i] * a[j];
			if (i == 1) {
				if (mat[i][j] >= 0 && mat[i][j] < MAX_S) {
					dp[1][mat[i][j]] = 1;
				} else if (mat[i][j] < 0) {
					dp[1][MAX_S - mat[i][j]] = 1;
				}
			}
		}
	}
	for (int i = 2; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int k = 0; k < MAX_S; ++k) {
				if (mat[i][j] + k >= 0 && mat[i][j] + k < MAX_S) {
					dp[i][mat[i][j] + k] += dp[i - 1][k];
				} else if (mat[i][j] + k < 0) {
					dp[i][MAX_S - (mat[i][j] + k)] += dp[i - 1][k];
				}
			}
			for (int k = MAX_S; k < MAX_S * 2; ++k) {
				int t = MAX_S - k;
				if (mat[i][j] + t >= 0) 
					dp[i][mat[i][j] + t] += dp[i - 1][k];
				else if (mat[i][j] + t < 0)
					dp[i][MAX_S - (mat[i][j] + t)] += dp[i - 1][k];
			}
		}
	}
	int ans = dp[m][0];
	printf("%d\n", ans);
	return 0;
}


