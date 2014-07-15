#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_N = 9;
const int MAX_K = 17;
const int INF = 0x3f3f3f3f;

int n;
int a[MAX_N][MAX_N];
int rec[MAX_N][MAX_N];
int s[MAX_N][MAX_N][MAX_N][MAX_N];
int dp[MAX_K][MAX_N][MAX_N][MAX_N][MAX_N];

int main() {
	scanf("%d", &n);
	int sum = 0;
	for (int i = 1; i <= 8; ++i) {
		for (int j = 1; j <= 8; ++j) {
			scanf("%d", &a[i][j]);
			sum += a[i][j];
		}
	}
	for (int i = 1; i <= 8; ++i) {
		for (int j = 1; j <= 8; ++j) {
			rec[i][j] = rec[i - 1][j] + rec[i][j - 1] - rec[i - 1][j - 1] + a[i][j];	
		} 
	}
	for (int i = 1; i <= 8; ++i) {
		for (int j = 1; j <= 8; ++j) {
			for (int k = i; k <= 8; ++k) {
				for (int l = j; l <= 8; ++l) {
					s[i][j][k][l] = rec[k][l] - rec[k][j - 1] - rec[i - 1][l] + rec[i - 1][j - 1];
					s[i][j][k][l] = s[i][j][k][l] * s[i][j][k][l];
					dp[0][i][j][k][l] = s[i][j][k][l];
				}
			}
		}
	}

	for (int k = 1; k < n; ++k) {
		for (int x1 = 1; x1 <= 8; ++x1) {
			for (int y1 = 1; y1 <= 8; ++y1) {
				for (int x2 = x1; x2 <= 8; ++x2) {
					for (int y2 = y1; y2 <= 8; ++y2) {
						dp[k][x1][y1][x2][y2] = INF;
						for (int a = x1; a < x2; ++a) {
							dp[k][x1][y1][x2][y2] = min(min(dp[k - 1][x1][y1][a][y2] + s[a + 1][y1][x2][y2], dp[k - 1][a + 1][y1][x2][y2] +
											s[x1][y1][a][y2]), dp[k][x1][y1][x2][y2]);
						}
						for (int b = y1; b < y2; ++b) {
							dp[k][x1][y1][x2][y2] = min(min(dp[k - 1][x1][y1][x2][b] + s[x1][b + 1][x2][y2], dp[k - 1][x1][b + 1][x2][y2] + s[x1][y1][x2][b]), dp[k][x1][y1][x2][y2]);
						}
					}
				}
			}
		}
	}
	double avg = 1. * sum / n;
	double ans = dp[n - 1][1][1][8][8] * 1. / n - avg * avg;
	printf("%.3f\n", sqrt(ans));
	return 0;
}
