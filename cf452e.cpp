#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 300007;

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

const int MOD = 1000000007;
typedef pair<int,int> pii;

char str[MAX_N], temp[MAX_N];
int f[MAX_N], d[MAX_N], c[MAX_N][4]; //排名前i中,j1,j2,j3串长度
vector<int> v[MAX_N]; // 高度为i的排名
set<pii> s;

long long cal(int l, int r) {
	int a1 = c[r][1] - c[l - 1][1];
	int a2 = c[r][2] - c[l - 1][2];
	int a3 = c[r][3] - c[l - 1][3];
	if (a1 == 0 || a2 == 0 || a3 == 0) return -1;
	return 1LL * a1 * a2 * a3;
}

int main() {
	int l = MAX_N;
	scanf("%s", temp);
	int n = 0;
	long long get = 1;
	l = min(l, (int) strlen(temp));
	for (int i = 0; temp[i]; ++i) {
		f[n] = 1;
		str[n++] = temp[i] - 'a' + 5;
	}
	get *= (int) strlen(temp);
	str[n++] = 'b' - 'a';
	scanf("%s", temp);
	l = min(l, (int) strlen(temp));
	for (int i = 0; temp[i]; ++i) {
		f[n] = 2;
		str[n++] = temp[i] - 'a' + 5;
	}
	get = (get * (int) strlen(temp)) % MOD;
	str[n++] = 'c' - 'a';
	scanf("%s", temp);
	l = min(l, (int) strlen(temp));
	for (int i = 0; temp[i]; ++i) {
		f[n] = 3;
		str[n++] = temp[i] - 'a' + 5;
	}
	get = (get * (int) strlen(temp)) % MOD;
	str[n++] = 'd' - 'a';
	for (int i = 0; i < n; ++i) {
		d[i] = str[i];	
	}
	d[n] = 0;
	Suffix ans;
	ans.DA(d, sa, n + 1, 32);
	ans.calheight(d, sa, n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < 4; ++j) {
			c[i][j] = c[i - 1][j] + (f[sa[i]] == j);
		}
		v[height[i]].push_back(i);
	}
	s.insert(make_pair(1, n));
	set<pii>::iterator it = s.begin();
	for (int i = 0; i < l; ++i) {
		int len = (int)v[i].size();	
		for (int j = 0; j < len; ++j) {
			int hRank = v[i][j];
			pii now = make_pair(hRank, MOD);
			it = s.upper_bound(now);
			if (it == s.begin()) 
				continue;
			--it;
			if (it->first < hRank && hRank <= it->second) {
				long long t = cal(it->first, it->second);
				if (t != -1) get = (get - t + MOD) % MOD;
				t = cal(it->first, hRank - 1);
				if (t != -1) {
					get = (get + t) % MOD;
					s.insert(make_pair(it->first, hRank - 1));
				}
				t = cal(hRank, it->second);
				if (t != -1) {
					get = (get + t) % MOD;
					s.insert(make_pair(hRank, it->second));
				}
				s.erase(it);
			}
		}
		printf("%I64d\n", (get + MOD) % MOD);
	}
	return 0;
}


