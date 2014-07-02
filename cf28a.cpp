#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

const int MAX_N = 507;

struct Point {
	int x, y;
};

int n, m;
Point nail[MAX_N];
int len[MAX_N], ans[MAX_N];
bool vis[MAX_N];

int dist(int i, int j) {
	return abs(nail[i].x - nail[j].x) + abs(nail[i].y - nail[j].y);
}

bool check(int i, int j) {
	return len[j] == dist(i - 1, i) + dist(i, i + 1);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &nail[i].x, &nail[i].y);
	}
	nail[0] = nail[n], nail[n + 1] = nail[1];
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &len[i]);
	}
	bool no = false;
	memset(ans, -1, sizeof ans);
	for (int i = 1; i <= n; i += 2) {
		bool f = false;
		for (int j = 1; j <= m; ++j) {
			if (!vis[j] && check(i, j)) {
				vis[j] = true;
				ans[i] = j;
				f = true;
				break;
			}
		}
		if (!f) {
			no = true;
			break;
		}
	}
	if (!no) {
		puts("YES");
		for (int i = 1; i <= n; ++i) {
			if (~ans[i]) printf("%d ", ans[i]);
			else printf("-1 ");
		}
	} else {
		memset(vis, false, sizeof vis);
		memset(ans, -1, sizeof ans);
		for (int i = 2; i <= n; i += 2) {
			bool f = false;
			for (int j = 1; j <= m; ++j) {
				if (!vis[j] && check(i, j)) {
					vis[j] = true;
					ans[i] = j;
					f = true;
					break;
				}
			}
			if (!f) {
				puts("NO");
				return 0;
			}
		}
		puts("YES");
		for (int i = 1; i <= n; ++i) {
			if (~ans[i]) printf("%d ", ans[i]);
			else printf("-1 ");
		}
	}
	puts("");
	return 0;
}
