#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int,int> pii;
typedef pair<pii,int> three;

const int MAX_N = 20;
const int MAX_S = 1<<15;
const int INF = 0x3f3f3f3f;
const int dir[4][2] = {-1,0, 1,0, 0,1, 0,-1};

struct Tunnel {
	int u1, v1, u2, v2;
	Tunnel() {

	}
	Tunnel(int _u, int _v, int _u1, int _v1) {
		u1 = _u, v1 = _v, u2 = _u1, v2 = _v1;
	}
};

int n, m;
Tunnel tunnel[MAX_N];
char mat[MAX_N][MAX_N];
int dp[MAX_S][MAX_N];
int dist[MAX_N][MAX_N];
int vis[MAX_N][MAX_N];

int bfs(int x, int y) {
	queue<pii> q;
	memset(vis, -1, sizeof vis);
	q.push(make_pair(tunnel[x].u2, tunnel[x].v2));
	vis[tunnel[x].u2][tunnel[x].v2] = 0;
	while (!q.empty()) {
		pii u = q.front();
		q.pop();
		if (u.first == tunnel[y].u1 && u.second == tunnel[y].v1) return vis[u.first][u.second];
		for (int i = 0; i < 4; ++i) {
			int nx = u.first + dir[i][0];
			int ny = u.second + dir[i][1];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && -1 == vis[nx][ny] && mat[nx][ny] == '.') {
				q.push(make_pair(nx, ny));
				vis[nx][ny] = vis[u.first][u.second] + 1;
			}
		}
	}
	return -1;
} 

int main() {
	while (2 == scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; ++i) {
			scanf("%s", mat[i] + 1);
		}
		for (int i = 0; i < m; ++i) {
			int u1, v1, u2, v2;
			scanf("%d%d%d%d", &u1, &v1, &u2, &v2);
			tunnel[i] = Tunnel(u1, v1, u2, v2);
		}
		memset(dist, 0, sizeof dist);
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < m; ++j) {
				if (i == j)
				  continue;
				else 
				  dist[i][j] = bfs(i, j);
			}
		}

		int limit = (1 << m);
		
		for (int i = 0; i <= limit; ++i) {
			fill(dp[i], dp[i] + m + 1, INF);
		}
		for (int i = 0; i < m; ++i) {
			dp[(1 << i)][i] = 0;
		}
		for (int s = 0; s < limit; ++s) {
			for (int v = 0; v < m; ++v) {
				if ((s >> v & 1) == 0) continue;
				for (int u = 0; u < m; ++u) {
					if (dist[u][v] == -1) 
					  continue;
					if ((s >> u & 1) != 0) {
						dp[s][v] = min(dp[s][v], dp[s ^ ( 1 << v)][u] + dist[u][v]);
					}
				}
			}
		}
		int ans = INF;
		for (int i = 0; i < m; ++i) {
			ans = min(ans, dp[limit - 1][i]);
		}
		if (ans == INF) puts("-1");
		else printf("%d\n", ans);
	}
	return 0;
}
