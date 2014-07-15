#include <cstdio>
#include <cstring>

const int MAX_N = 5;

int n, m;
char maz[MAX_N][MAX_N];
char ans[MAX_N*100][MAX_N*100];

void dfs(int r, int c, char ch, int f) {
	if (f == 0) ans[r][c] = ch;
	else {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				dfs(r * n + i, c * n + j, (ch == '*' ? '*' : maz[i][j]), f - 1);
			}
		}
	}
}


int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%s", maz[i]);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			dfs(i, j, maz[i][j], m - 1);
		}
	}
	for (int i = 0; ans[i][0]; ++i) 
	  puts(ans[i]);
	return 0;
}
