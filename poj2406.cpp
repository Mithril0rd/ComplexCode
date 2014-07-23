#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 4000007;

int sa[MAX_N], wa[MAX_N], wb[MAX_N], ws[MAX_N], rank[MAX_N], height[MAX_N];
int wss[MAX_N], wv[MAX_N];

#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)

struct Suffix {
	int c0(int *r, int a, int b) {
	 return r[a] == r[b] && r[a+1] == r[b+1] && r[a+2] == r[b+2];
	}
	int c12(int k,int *r,int a,int b) {
	   if(k == 2)
        return r[a] < r[b] || ( r[a] == r[b] && c12(1,r,a+1,b+1) );
	  else return r[a] < r[b] || ( r[a] == r[b] && wv[a+1] < wv[b+1] );
	}
	void sort(int *r,int *a,int *b,int n,int m)	{
	    int i;
	    for(i = 0;i < n;i++)wv[i] = r[a[i]];
	    for(i = 0;i < m;i++)wss[i] = 0;
	    for(i = 0;i < n;i++)wss[wv[i]]++;
	    for(i = 1;i < m;i++)wss[i] += wss[i-1];
	    for(i = n-1;i >= 0;i--)
		b[--wss[wv[i]]] = a[i];
	}
	void dc3(int *r,int *sa,int n,int m) {
	    int i, j, *rn = r + n;
	    int *san = sa + n, ta = 0, tb = (n+1)/3, tbc = 0, p;
	    r[n] = r[n+1] = 0;
	    for(i = 0;i < n;i++)if(i %3 != 0)wa[tbc++] = i;
	    sort(r + 2, wa, wb, tbc, m);
	    sort(r + 1, wb, wa, tbc, m);
	    sort(r, wa, wb, tbc, m);
	    for(p = 1, rn[F(wb[0])] = 0, i = 1;i < tbc;i++)
		rn[F(wb[i])] = c0(r, wb[i-1], wb[i]) ? p - 1 : p++;
	    if(p < tbc)dc3(rn,san,tbc,p);
	    else for(i = 0;i < tbc;i++)san[rn[i]] = i;
	    for(i = 0;i < tbc;i++) if(san[i] < tb)wb[ta++] = san[i] * 3;
	    if(n % 3 == 1)wb[ta++] = n - 1;
	    sort(r, wb, wa, ta, m);
	    for(i = 0;i < tbc;i++)wv[wb[i] = G(san[i])] = i;
	    for(i = 0, j = 0, p = 0;i < ta && j < tbc;p++)
		sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
	    for(;i < ta;p++)sa[p] = wa[i++];
	    for(;j < tbc;p++)sa[p] = wb[j++];
	}
	void DA(int str[],int sa[],int n,int m)	{
	    for(int i = n;i < n*3;i++)
			str[i] = 0;
	    dc3(str, sa, n+1, m);
	    int i,j,k = 0;
	    for(i = 0;i <= n;i++)rank[sa[i]] = i;
	    for(i = 0;i < n; i++)
	    {
			if(k) k--;
			j = sa[rank[i]-1];
			while(str[i+k] == str[j+k]) k++;
			height[rank[i]] = k;
	    }
	}
};

char str[MAX_N];
int d[MAX_N];

int main() {
	while (1 == scanf("%s", str)) {
		if (strcmp(str, ".") == 0) break;
		int len = (int) strlen(str);
		for (int i = 0; i < len; ++i) {
			d[i] = str[i];
		}
		d[len] = 0;
		Suffix ans;
		ans.DA(d, sa, len + 1, 128);
		bool f = false;
	//	for (int i = 1; i <= len; ++i) printf("%d ", sa[i]); puts("");
		for (int i = 1; i * 2 <= len; ++i) {
			if (len % i == 0) {
				if (rank[0] < rank[i]) continue;
				int lcp = 0;	
				for (int j = rank[i] + 1; j <= rank[0]; ++j) {
					lcp = max(lcp, height[j]);
				}
			//	printf("%s %d %d\n", str, i, lcp);
				if (lcp == len - i) {
					printf("%d\n", len / i);
					f = true;
					break;
				}
			}
		}
		if (!f) puts("1");
	}
	return 0;
}
