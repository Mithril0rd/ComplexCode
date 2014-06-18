#include <cstdio>
#include <queue>

using namespace std;

struct node {
	int x, y, tim, dir;
};

const int MAX_N = 7;
const int dir[5][2] = {0,0, 1,0, -1,0, 0,1, 0,-1};

queue<node> q;
int mat[MAX_N][MAX_N];

void bfs(int x, int y) {
	mat[x][y] = 0;
	while (!q.empty()) q.pop();
	for (int i = 1; i <= 4; ++i) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (nx >= 1 && nx <= 6 && ny >= 1 && ny <= 6)
		  q.push((node) {nx, ny, 1, i });
	}
	int nowTime = 1;
	while (!q.empty()) {
		while (!q.empty() && q.front().tim == nowTime) {
			node now = q.front(); q.pop();
			if (mat[now.x][now.y]) 
			  ++mat[now.x][now.y];
			else {
				int nx = now.x + dir[now.dir][0];
				int ny = now.y + dir[now.dir][1];
				if (nx >= 1 && nx <= 6 && ny >= 1 && ny <= 6) 
				  q.push((node) {nx, ny, nowTime + 1, now.dir});
			}
		}
		for (int i = 1; i <= 6; ++i) {
			for (int j = 1; j <= 6; ++j) {
				if (mat[i][j] > 4){
					mat[i][j] = 0;
					for (int k = 1; k <= 4; ++k) {
						int nx = i + dir[k][0];
						int ny = j + dir[k][1];
						if (nx >= 1 && nx <= 6 && ny >= 1 && ny <= 6) 
						  q.push((node) {nx, ny, nowTime + 1, k});
					}
				}
			}
		}
		++nowTime;
	}
}

int main() {
	while (EOF != scanf("%d", &mat[1][1])) {
		for (int i = 1; i <= 6; ++i) {
			for (int j = 1; j <= 6; ++j) {
				if (i == 1 && j == 1) 
					continue;
				scanf("%d", &mat[i][j]);
			}
		}
		int m;
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			if (++mat[x][y] > 4) {
				bfs(x, y);
			}
		}
		for (int i = 1; i <= 6; ++i) {
			for (int j = 1; j <= 6; ++j) {
				if (j == 1) 
				  printf("%d", mat[i][j]);
				else printf(" %d", mat[i][j]);
			}
			puts("");
		}
		puts("");

	}
	return 0;
}
