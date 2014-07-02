#include <cstdio>
#include <cstring>

const int MAX_N = 107;

int n;
int a[MAX_N], b[MAX_N];
bool edge[MAX_N][MAX_N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &b[i]);
		edge[i][i] = true;
		if (i - b[i] >= 1) edge[i][i - b[i]] = true;
		if (i + b[i] <= n) edge[i][i + b[i]] = true;
	}
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				edge[i][j] = edge[i][j] | edge[i][k] & edge[k][j] | edge[i][k] & edge[j][k];
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (!edge[i][a[i]]) {
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
