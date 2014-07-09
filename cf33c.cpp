#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

const int MAX_N = 100007;
const int INF = INT_MAX;

int n;
int a[MAX_N], sum[MAX_N + 1];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    sum[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
        sum[i] = sum[i + 1] + a[i];
    }
	int ans = -INF + 1, suffix = INF, prefix = sum[0];
	for (int i = n; i >= 0; --i) {
		suffix = min(suffix, sum[i]);
		if (i < n) prefix -= a[i];
		ans = max(ans, sum[0] - 2 * prefix - 2 * suffix);
	}
	printf("%d\n", ans);
    return 0;
}
