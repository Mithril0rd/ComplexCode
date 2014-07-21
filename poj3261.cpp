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

int n, k;
int a[MAX_N], b[MAX_N];

bool check(int x) {
	int i = 2, cnt = 0;
	while (i <= n) {
		while (i <= n && height[i] < x) ++i;
		if (i > n) break;
		cnt = 1;
		while (i <= n && height[i] >= x) {
			if (++cnt >= k) return true;
			++i;
		}
	}
	return false;
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	sort(b, b + n);
	for (int i = 0; i < n; ++i) {
		a[i] = lower_bound(b, b + n, a[i]) - b;
		++a[i];
	}
	a[n] = 0;
	Suffix ans;
	ans.DA(a, sa, n + 1, MAX_N - 1);
	ans.calheight(a, sa, n);
//	for (int i = 1; i <= n; ++i) printf("%d ", height[i]); puts("");
	int l = 1, r = n; 
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) l = mid;
		else r = mid;
	}
//	if (check(r)) l = r;
	printf("%d\n", l);
	return 0;
}
