#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 20007;

int sa[MAX_N], wa[MAX_N], wb[MAX_N], ws[MAX_N], rank[MAX_N], height[MAX_N];

struct Suffix {
	int cmp(int *r, int a, int b, int d) {
		return r[a] == r[b] && r[a + d] == r[b + d];
	}
	void DA(int *r, int *sa, int n, int m) {
		int *x = wa, *y = wb;
		for (int i = 0; i < m; ++i) ws[i] = 0;
		for (int i = 0; i < n; ++i) ++ws[x[i] = r[i]];
		for (int i = 1; i < m; ++i) ws[i] += ws[i - 1];
		for (int i = n - 1; i >= 0; --i) sa[--ws[x[i]]] = i;
		for (int k = 1; k <= n; k <<= 1) {
			int p = 0;
			for (int i = n - k; i < n; ++i) y[p++] = i;
			for (int i = 0; i < n; ++i) if (sa[i] >= k) y[p++] = sa[i] - k;
			for (int i = 0; i < m; ++i) ws[i] = 0;
			for (int i = 0; i < n; ++i) ++ws[x[y[i]]];
			for (int i = 1; i < m; ++i) ws[i] += ws[i - 1];
			for (int i = n - 1; i >= 0; --i) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y);
			p = 1, x[sa[0]] = 0;
			for (int i = 1; i < n; ++i) x[sa[i]] = cmp(y, sa[i - 1], sa[i], k) ? p - 1 : p++;
			if (p >= n) break;
			m = p;
		}
	}
	void calheight(int *r, int *sa, int n) {
		for (int i = 1; i <= n; ++i) rank[sa[i]] = i;
		for (int i = 0, k = 0; i < n; ++i) {
			if (k) --k;
			int j = sa[rank[i] - 1];
			while (i + k < n && j + k < n && r[i + k] == r[j + k]) ++k;
			height[rank[i]] = k;
		}
	}
};


char str[MAX_N];
int d[MAX_N];

void solve() {
	int len = strlen(str);
	for (int i = 0; i < len; ++i) d[i] = (int) str[i];
	Suffix ans;
	d[len] = 0;
	ans.DA(d, sa, len + 1, 128);
	ans.calheight(d, sa, len);
	long long ret = (len + 1) * len / 2;
	for (int i = 2; i <= len; ++i) {
		ret -= height[i];
	}
	printf("%lld\n", ret);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		memset(sa, 0, sizeof sa);
		memset(wa, 0, sizeof wa);
		memset(wb, 0, sizeof wb);
		memset(height, 0, sizeof height);
		memset(rank, 0, sizeof rank);
		scanf("%s", str);
		solve();
	}
	return 0;
}

