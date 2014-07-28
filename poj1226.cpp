#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>

using namespace std;

const int MAX_N = 300007;

#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)

int wa[MAX_N], wb[MAX_N], wv[MAX_N], ws[MAX_N];
int height[MAX_N], rank[MAX_N], sa[MAX_N];

struct Suffix {
	int c0(int *r, int a, int b) {
		return r[a] == r[b] && r[a+1] == r[b+1] && r[a+2] == r[b+2];
	}
	int c12(int k, int *r, int a, int b) {
		if(k==2)
		  return r[a] < r[b] || r[a] == r[b] && c12(1, r, a+1, b+1);
		else 
		  return r[a] < r[b] || r[a] == r[b] && wv[a+1] < wv[b+1];
	}
	void sort(int *r,int *a,int *b,int n,int m)	{
		int i;
		for(i = 0; i < n; i++) wv[i] = r[a[i]];
		for(i = 0; i < m; i++) ws[i] = 0;
		for(i = 0; i < n; i++) ws[wv[i]]++;
		for(i = 1; i < m; i++) ws[i] += ws[i-1];
		for(i = n-1; i >= 0; i--) b[--ws[wv[i]]] = a[i];

	}
	void dc3(int *r, int *sa, int n, int m) {
		int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n+1) / 3,tbc = 0, p;
		r[n] = r[n+1] = 0;
		for(i = 0; i < n; i++) if(i % 3 != 0) wa[tbc++] = i;
		sort(r + 2, wa, wb, tbc, m);
		sort(r + 1, wb, wa, tbc, m);
		sort(r, wa, wb, tbc, m);
		for(p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
			rn[F(wb[i])] = c0(r, wb[i-1], wb[i]) ? p - 1 : p++;
		if(p < tbc) dc3(rn, san, tbc, p);
		else for(i = 0; i < tbc; i++) san[rn[i]]=i;	
		for(i = 0; i < tbc; i++) if(san[i] < tb) wb[ta++] = san[i]*3;
		if(n % 3 == 1) wb[ta++] = n-1;
		sort(r, wb, wa, ta, m);
		for(i = 0; i < tbc; i++) wv[wb[i] = G(san[i])] = i;
		for(i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
		sa[p] = c12(wb[j]%3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
		for(; i<ta; p++) sa[p] = wa[i++];
		for(; j<tbc; p++) sa[p] = wb[j++];
	}
	void calheight(int *r, int *sa, int n) {
		for (int i = 1; i <= n; ++i) rank[sa[i]] = i;
		for (int i = 0, k = 0; i < n; ++i) {
			if(k) --k;
			int j = sa[rank[i]-1];
			while (i + k < n && j + k < n && r[i+k] == r[j+k]) ++k;
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

int n, m;
char str[107][107], s[MAX_N];
int sumLen[107], d[MAX_N];
int f[MAX_N];

bool check( int len) {  
	bool found[107] = {false};
	int i = 1; 
	while (i <= m) {
		while (i <= m && height[i] < len) ++i;
		if (i > m) break;
		memset(found, false, sizeof found);
		int cnt = 1;	
		found[f[sa[i - 1]]] = true;
		while (i <= m && height[i] >= len) {
			if (!found[f[sa[i]]]) {
				found[f[sa[i]]] = true;
				if (++cnt >= n) return true;
			}
			if (++i > m) break;
		}
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d", &n);
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str[i]);
		}
		if (n == 1) {
			int len = (int) strlen(str[1]);
			printf("%d\n", len);
			continue;
		}
		int len = 0;
		int limit = MAX_N;
		for (int i = 1; i <= n; ++i) {
			int tLen = (int) strlen(str[i]);
			sumLen[i] = sumLen[i - 1] + tLen + 1;
			limit = min(limit, tLen);
			for (int j = 0; j < tLen; ++j) {
				f[len] = i;
				s[len++] = str[i][j];
			}
			s[len++] = '$';
			for (int j = tLen - 1; j >= 0; --j) {
				f[len] = i;
				s[len++] = str[i][j];
			}
			s[len++] = '$';
		}
	//	puts(s);
		int big = 70;
		for (int i = 0; i < len; ++i) {
			if (s[i] == '$') d[i] = big++;
			else {
				if (islower(s[i])) d[i] = s[i] - 'a' + 1;
				else if (isupper(s[i])) d[i] = s[i] - 'A' + 27;
			}
	//		printf("%d ", d[i]);
		}
	
		d[len] = 0;
		Suffix ans;
		ans.dc3(d, sa, len + 1, big + 1);
		ans.calheight(d, sa, len);
		m = len;
		int l = 0, r = limit;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (check(mid)) l = mid;
			else r = mid - 1;
		}
		if (check(r)) l = r;
		printf("%d\n", l);
	}
	return 0;
}
