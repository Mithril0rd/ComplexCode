#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 107;
const int INF = 0x3f3f3f3f;

int n, m, k;
int a[MAX_N][MAX_N];
int dp[MAX_N][MAX_N][12];
int pre[MAX_N][MAX_N][12];
int cnt;

void dfs(int *ans, int i, int j, int r) {
//rintf("%d %d\n", i, j);
	if (i == n) return ;
	else {
		if (pre[i][j][r] == j - 1)
		  dfs(ans, i + 1, j - 1, (dp[i][j][r] - a[i][j]) % (k + 1));
		else 
		  dfs(ans, i + 1, j + 1, (dp[i][j][r] - a[i][j]) % (k + 1));
		ans[cnt++] = pre[i][j][r];
		//		printf("%d %d %d\n", i, j, pre[i][j][r]);
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	char str[MAX_N];
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str + 1);
		for (int j = 1; j <= m; ++j) {
			a[i][j] = str[j] - '0'; 
		}
	}
	memset(dp, -1, sizeof dp);
	for (int i = 1; i <= m; ++i) {
		dp[n][i][a[n][i] % (k + 1)] = a[n][i];
	}
	for (int i = n - 1; i >= 1; --i) {
		for (int j = 1; j <= m; ++j) {
			for (int r = 0; r <= k; ++r) {
				if (j > 1) {
					if (dp[i + 1][j - 1][r] >= 0)
						if (dp[i + 1][j - 1][r] + a[i][j] > dp[i][j][(r + a[i][j]) % (k + 1)]) {
							dp[i][j][(r + a[i][j]) % (k + 1)] = dp[i + 1][j - 1][r] + a[i][j];
							pre[i][j][(r + a[i][j]) % (k + 1)] = j - 1;
						}
				}
				if (j < m) {
					if (dp[i + 1][j + 1][r] >= 0)
						if (dp[i + 1][j + 1][r] + a[i][j] > dp[i][j][(r + a[i][j]) % (k + 1)]) {
							dp[i][j][(r + a[i][j]) % (k + 1)] = dp[i + 1][j + 1][r] + a[i][j];
							pre[i][j][(r + a[i][j]) % (k + 1)] = j + 1;
						}
				}
			}
		}
	}
	int idx = 1, Max = -1;
	for (int i = 1; i <= m; ++i) {	
		if (dp[1][i][0] > Max) {
			Max = dp[1][i][0];
			idx = i;
		}
	} 
	int ans[MAX_N];
	dfs(ans, 1, idx, 0);
	ans[cnt++] = idx;
	puts("");
	if (Max == -1) puts("-1");
	else {
		printf("%d\n", Max);
		printf("%d\n", ans[0]);
		for (int i = 0; i + 1 < cnt; ++i) {
			if (ans[i + 1] > ans[i]) putchar('R');
			else putchar('L');
		}
		puts("");
	}
	return 0;
}



