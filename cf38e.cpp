#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_N = 3007;

typedef long long ll;

struct Node {
	int x, c;
	Node() {

	}
	Node(int i, int j) {
		x = i, c = j;
	}
	bool operator < (const Node &rhs) const {
		return x < rhs.x || (x == rhs.x && c < rhs.c);
	}
};

int n;
Node marble[MAX_N];
ll dp[MAX_N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &marble[i].x, &marble[i].c);
	}
	sort(marble + 1, marble + 1 + n);
	dp[1] = marble[1].c;
	for (int i = 2; i <= n; ++i) {
		ll cost = 0;
		dp[i] = dp[i - 1] + marble[i].c;
		for (int j = i - 1; j >= 1; --j) {
			cost += (ll)abs(marble[j].x - marble[j + 1].x) * (i - j);
			dp[i] = min(dp[i], dp[j - 1] + marble[j].c + cost);
		}
	}
	printf("%lld\n", dp[n]);
	return 0;
}
