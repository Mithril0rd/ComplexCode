
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 37;
const int INF = 0x3f3f3f3f;

int n;
int ans;
int T[MAX_N][MAX_N];
int l[MAX_N], r[MAX_N];
int deadline[MAX_N];

void dfs(int u, int cost, int sum, int num) {
	if (sum >= ans) return ;
	for (int v = r[0]; v > 0; v = r[v]) {
		if (cost + T[u][v] > deadline[v])
		  return ;
	}
	r[l[u]] = r[u], l[r[u]] = l[u];
	if (r[0] == 0) {
		ans = min(ans, sum);
		r[l[u]] = l[r[u]] = u;
		return ;
	}
	for (int v = r[0]; v > 0; v = r[v]) {
		dfs(v, cost + T[u][v], sum + T[u][v] * num, num - 1);
	}
	r[l[u]] = l[r[u]] = u;
}  

int main() {
	while (1 == scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				scanf("%d", &T[i][j]);
			}
		}
		for (int k = 1; k <= n; ++k) {
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					T[i][j] = min(T[i][j], T[i][k] + T[k][j]);
				}
			}
		}

		for (int i = 2; i <= n; ++i) {
			scanf("%d", &deadline[i]);
		}
		memset(l, 0, sizeof l);
		memset(r, 0, sizeof r);
		for (int i = 1; i <= n; ++i) {
			l[i] = i - 1, r[i] = i + 1; 
		}
		l[0] = n, r[0] = 1;
		r[n] = 0;
	    ans = INF;  
        dfs(1, 0, 0, n - 1);  
		if (ans == INF) puts("-1");
		else printf("%d\n", ans);
	}
	return 0;
}
