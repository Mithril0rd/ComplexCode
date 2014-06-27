#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>

using namespace std; 

const int MAX_N = 507;

int n, m;
int a[MAX_N], b[MAX_N];
int dp[MAX_N][MAX_N], path[MAX_N][MAX_N]; 
stack<int> s;

void print(int i, int j) {
	if (i == 0 || j == 0) 
		return ;
	if (~path[i][j]) {
		print(i - 1, path[i][j]);
		printf("%d ", b[j]);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &b[i]);
	}
	memset(path, -1, sizeof path);
	int ans = 0, x = 0, y = 0;
	for (int i = 1; i <= n; ++i) {
		int idx = 0, Max = 0;
		for (int j = 1; j <= m; ++j) {
			dp[i][j] = dp[i - 1][j];
			if (a[i] > b[j]) {
				if (dp[i - 1][j] > Max) {
					Max = dp[i - 1][j];
					idx = j;
				}
			} else if (a[i] == b[j]) {
				dp[i][j] = Max + 1;
				path[i][j] = idx;
			} 
			if (dp[i][j] > ans) {
				ans = dp[i][j];
				x = i, y = j;
			}
		}
	}
	printf("%d\n", ans);
	int ans1 = ans; 
	while (ans1 > 0) {
		if (~path[x][y]) s.push(b[y]), --ans1, y = path[x][y];
		--x;
	}
	while (!s.empty())
		printf("%d ", s.top()), s.pop();
	puts("");
	return 0;
}
