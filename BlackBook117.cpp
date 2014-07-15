#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_N = 107;

int n;
int List[MAX_N];
char str[MAX_N];
bool e[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];
vector<int> ans;

bool Meet(int a, int b) {
	if (~dp[a][b]) return dp[a][b];
	if (a + 1 == b) return dp[a][b] = 1;
	int can = false;
	for (int i = a + 1; i < b; ++i) {
		if ((e[List[a]][List[i]] || e[List[b]][List[i]]) && Meet(a, i) && Meet(i, b)) {
			can = true;
			break;
		}
	}
	return dp[a][b] = can;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str + 1);
			for (int j = 1; j <= n; ++j) {
				e[i][j] = str[j] == '1';
			}
		}
		ans.clear();
		for (int i = 1; i <= n; ++i) {
			memset(dp, -1, sizeof dp);
			int t = i;
			for (int j = 0; j <= n; ++j) {
				if (t <= n) List[j] = t;
				else List[j] = t - n;
				++t;
			}
			if (Meet(0, n))
			  ans.push_back(i);
		}
		int len = (int) ans.size();
		printf("%d\n", len);
		for (int i = 0; i < len; ++i) {
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}
