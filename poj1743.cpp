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

int n;
int a[MAX_N];

bool check(int x) {
	int l = 0, r = 0, i = 1;
	while (i <= n) {
		while (i <= n && height[i] < x) ++i;
		if (i > n) break;
		l = sa[i - 1], r = sa[i - 1];
		while (i <= n && height[i] >= x) {
			l = min(l, sa[i]);
			r = max(r, sa[i]);
			++i;
			if (r - l >= x) return true;
		}
	}
	return false;
}

int main() {
	while (1 == scanf("%d", &n)) {
		if (0 == n) break;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		if (n < 10) {
			puts("0");
			continue;
		}
		for (int i = 0; i + 1 < n; ++i) {
			a[i] = a[i] - a[i + 1] + 100;
		}
		a[n - 1] = 0;
		Suffix ans;
		ans.DA(a, sa, n, 200);
		ans.calheight(a, sa, n - 1);
		int l = 1, r = (n + 1) / 2;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (check(mid)) l = mid;
			else r = mid;
		}
		if (l < 4) puts("0");
		else printf("%d\n", l + 1);
	}
	return 0;
}
