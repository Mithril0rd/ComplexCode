#include <cstdio>
#include <cstring>

const int MAX_N = 1007;

int n, m, x, y;
double dp[MAX_N][MAX_N], A[MAX_N], B[MAX_N], C[MAX_N];

int main() {
	scanf("%d%d%d%d", &n, &m, &x, &y);
	if (1 == m) {
		double ans = 2. * (n - x);
		printf("%10f\n", ans);
		return 0;
	}
	for (int i = n - 1; i >= x; --i) {
		C[1] = dp[i + 1][1] / 2 + 3. / 2;
		C[m] = dp[i + 1][m] / 2 + 3. / 2;
		for (int j = 2; j <= m - 1; ++j) {
			C[j] = dp[i + 1][j] / 3 + 4.0 / 3;
		}
		A[1] = 1, B[1] = -0.5;
		double t = 0;
		int j = 2;
		for (j = 2; j <= m - 1; ++j) {
			t = 1.0 / 3 / A[j - 1];
			A[j] = t * B[j - 1] + 1;
			B[j] = -1. / 3;
			C[j] += t * C[j - 1];
		}
		t = 0.5 / A[j - 1];
		A[j] = t * B[j - 1] + 1;
		C[j] += t * C[j - 1];
		dp[i][m] = C[m] / A[m];
		for (j = m - 1; j >= 1; --j) {
			dp[i][j] = (C[j] - dp[i][j + 1] * B[j]) / A[j];
		}
	}
	double ans = dp[x][y];
	printf("%.10f\n", ans);
	return 0;
}
