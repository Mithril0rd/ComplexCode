#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 200007;

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

int RMQ[MAX_N], mm[MAX_N], best[13][MAX_N];

void initRMQ(int n) {
	mm[0] = -1;
	for (int i = 1; i <= n; ++i) {
		mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
	}
	for (int i = 1; i <= n; ++i) {
		best[0][i] = i;
	}
	for (int i = 1; i <= mm[n]; ++i) {
		for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
			int a = best[i - 1][j];
			int b = best[i - 1][j + (1 << (i - 1))];
			if (RMQ[a] < RMQ[b]) best[i][j] = a;
			else best[i][j] = b;
		}
	}
}

int query(int a, int b) {
	int t = mm[b - a + 1];
	b -= (1 << t) - 1;
	a = best[t][a], b = best[t][b];
	return RMQ[a] < RMQ[b] ? a : b;
}

int lcp(int a, int b) {
	a = rank[a], b = rank[b];
	if (a > b) swap(a, b);
	return height[query(a + 1, b)];
}

int n;
char str[MAX_N], temp[MAX_N];
int d[MAX_N];
int Stack[MAX_N], cnt[MAX_N];

int main() {
	int k;
	while (1 == scanf("%d", &k)) {
		if (0 == k) break;
		scanf("%s", temp);
		int l1 = (int) strlen(temp);
		for (int i = 0; i < l1; ++i) 
		  str[i] = temp[i];
		str[l1] = '$';
		scanf("%s", temp);
		int l2 = (int) strlen(temp);
		for (int i = 0; i < l2; ++i) 
		  str[i + l1 + 1] = temp[i];
		n = l1 + l2 + 1;
		for (int i = 0; i < n; ++i) {
			d[i] = str[i]; 
		}
		d[n] = 0;
		Suffix ans;
		ans.DA(d, sa, n + 1, 128);
		ans.calheight(d, sa, n);

		long long tot = 0, pre = 0, result = 0;
		int top = 0;
		for (int i = 1; i <= n; ++i) {
			if (height[i] < k) top = tot = 0;
			else {
				pre = 0;
				if (sa[i - 1] > l1) 
				  pre = 1, tot += height[i] - k + 1;
				while (top > 0 && Stack[top] >= height[i]) {
					tot -= cnt[top] * (Stack[top] - height[i]);
					pre += cnt[top--];
				}
		//		if (sa[i - 1] > l1 && sa[i] < l1) 
				  Stack[++top] = height[i], cnt[top] = pre;
				if (sa[i] < l1) 
				  result += tot;
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (height[i] < k) top = tot = 0;
			else {
				pre = 0;
				if (sa[i - 1] < l1)
				  pre = 1, tot += height[i] - k + 1;
				while (top > 0 && Stack[top] >= height[i]) {
					tot -= cnt[top] * (Stack[top] - height[i]);
					pre += cnt[top--];
				}
		//		if (sa[i - 1] < l1 && sa[i] > l1)
				  Stack[++top] = height[i], cnt[top] = pre;
				if (sa[i] > l1)
				  result += tot;
			}
		}
		printf("%lld\n", result);
	}
	return 0;
}
