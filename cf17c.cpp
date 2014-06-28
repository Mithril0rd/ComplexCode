#include <cstdio>
#include <cstring>

const int MAX_N = 157;
const int MOD = 51123987;

int n;
char str[MAX_N], uni[MAX_N];
int next[MAX_N][3]; // a, b, c
int dp[MAX_N][MAX_N/3][MAX_N/3][MAX_N/3];

int main() {
	scanf("%d%s", &n, str);
	int cnt = 0;
	uni[cnt++] = str[0];
	for (int i = 1; i < (int)strlen(str); ++i) {
		if (str[i] != str[i - 1]) 
			uni[cnt++] = str[i];
	}
	uni[cnt] = '\0';
	memset(next, -1, sizeof next);
	for (int i = 0; i < cnt; ++i) {
		for (int j = i; j < cnt; ++j) {
			if (uni[j] == 'a' && next[i][0] == -1) next[i][0] = j;
			else if (uni[j] == 'b' && next[i][1] == -1) next[i][1] = j;
			else if (uni[j] == 'c' && next[i][2] == -1) next[i][2] = j;
		}
	}

	int N = n / 3 + 1;
	dp[0][0][0][0] = 1;
	for (int i = 1; i <= cnt; ++i) {
		for (int a = 0; a <= N; ++a) {
			for (int b = 0; b <= N; ++b) {
				for (int c = 0; c <= N; ++c) {
					if (dp[i - 1][a][b][c] == 0) 
						continue;
					int nxt = next[i - 1][0];
					if (~nxt) {
						dp[nxt][a + 1][b][c] = (dp[i - 1][a][b][c] + dp[nxt][a + 1][b][c]) % MOD; 
					}
					nxt = next[i - 1][1];
					if (~nxt) {
						dp[nxt][a][b + 1][c] = (dp[i - 1][a][b][c] + dp[nxt][a][b + 1][c]) % MOD;
					}
					nxt = next[i - 1][2];
					if (~nxt) {
						dp[nxt][a][b][c + 1] = (dp[i - 1][a][b][c] + dp[nxt][a][b][c + 1]) % MOD;
					}
				}
			}
		}
	}
	int ans = 0;
	if (n % 3 == 0) {
		for (int i = 0; i < cnt; ++i) {
			ans = (ans + dp[i][n / 3][n / 3][n / 3]) % MOD;
		}
	} else if (n % 3 == 1) {
		for (int i = 0; i < cnt; ++i) {
			ans = (ans + dp[i][n / 3 + 1][n / 3][n / 3]) % MOD;
			ans = (ans + dp[i][n / 3][n / 3 + 1][n / 3]) % MOD;
			ans = (ans + dp[i][n / 3][n / 3][n / 3 + 1]) % MOD;
		}
	} else {
		for (int i = 0; i < cnt; ++i) {
			ans = (ans + dp[i][n / 3 + 1][n / 3 + 1][n / 3]) % MOD;
			ans = (ans + dp[i][n / 3][n / 3 + 1][n / 3 + 1]) % MOD;
			ans = (ans + dp[i][n / 3 + 1][n / 3][n / 3 + 1]) % MOD;
		}
	}
	printf("%d\n", ans);
	return 0;
}
