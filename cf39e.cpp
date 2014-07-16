#include <map>
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

long long pow(long long a, long long b, long long n) {
	long long ret = 1;
	for (int i = 0; i < b && ret < n; ++i) {
		ret *= a;
	}
	return ret;
}

map<pair<long long, long long>, int> dp;

int dfs(long long a, long long b, long long n) {
	if (pow(a, b, n) >= n) {
		return 1;
	}
	if (dp.count(make_pair(a, b)) == 0) {
		if (a == 1 && pow(a + 1, b, n) >= n) {
			dp[make_pair(a, b)] = 0;
		} else if (b == 1 && pow(a, b + 1, n) >= n) {
			dp[make_pair(a, b)] = (n - a) % 2 == 0 ? 1 : -1;
		} else {
			dp[make_pair(a, b)] = max(-dfs(a + 1, b, n), -dfs(a, b + 1, n));
		}
	}
	return dp[make_pair(a, b)];
}

const char* ans[] = {
	"Stas",
	"Missing",
	"Masha",
};

int main() {
	int a, b, n;
	scanf("%d%d%d", &a, &b, &n);
	puts(ans[dfs(a, b, n) + 1]);
	return 0;
}
