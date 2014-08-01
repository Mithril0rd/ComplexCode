#include<iostream>
#include<cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

const int maxn = 107;
const int maxe = 4007;
const int inf = 0x3f3f3f3f;

using namespace std;

struct Edge {
	int u, v, cap, cost, nxt;
	Edge(int _u, int _v, int _cap, int _cost, int _nxt) :
		u(_u), v(_v), cap(_cap), cost(_cost), nxt(_nxt){}
	Edge(){};
} edge[maxe];
int head[maxn];

struct ZKW_MinCostMaxFlow {
	int add;
	int cur[maxn];
	int dis[maxn];
	bool inq[maxn];
	queue<int> q;
	bool vis[maxn];
	int ss, tt, n;
	int min_cost, max_flow;
	void init() {
		memset(head, -1, sizeof(head));
		add = 0;
	}
	void insert(int u, int v, int cp, int ct) {
		edge[add] = Edge(u, v, cp, ct, head[u]);
		head[u] = add++;
		edge[add] = Edge(v, u, 0, -ct, head[v]);
		head[v] = add++;
	}
	int aug(int u, int flow) {
		if (u == tt) return flow;
		vis[u] = true;
		for (int i = cur[u]; i != -1; i = edge[i].nxt) {
			int v = edge[i].v;
			if (edge[i].cap && !vis[v] && dis[u] == dis[v] + edge[i].cost) {
				int tmp = aug(v, min(flow, edge[i].cap));
				edge[i].cap -= tmp;
				edge[i ^ 1].cap += tmp;
				cur[u] = i;
				if (tmp) return tmp;
			}
		}
		return 0;
	}
	bool modify_label() {
		int d = inf;
		for (int u = 0; u < n; u++) if (vis[u])
		for (int i = head[u]; i != -1; i = edge[i].nxt) {
			int v = edge[i].v;
			if (edge[i].cap && !vis[v])
				d = min(d, dis[v] + edge[i].cost - dis[u]);
		}
		if (d == inf) return false;
		for (int i = 0; i < n; ++i) if (vis[i]) {
			vis[i] = false;
			dis[i] += d;
		}
		return true;
	}

	pair<int, int> mincostmaxflow(int s, int t, int _n) {
		ss = s, tt = t, n = _n;
		min_cost = max_flow = 0;
		for (int i = 0; i < n; i++) dis[i] = 0;
		while (true) {
			for (int i = 0; i < n; i++) cur[i] = head[i];
			while (true) {
				for (int i = 0; i < n; i++) vis[i] = 0;
				int tmp = aug(s, inf);
				if (tmp == 0) break;
				max_flow += tmp;
				min_cost += tmp * dis[ss];
			}
			if (!modify_label()) break;
		}
		return make_pair(min_cost, max_flow);
	}
}solve;

int a[maxn][maxn];

int main() {
    int T;
    cin>>T;
    int kase=1;
    int n,m;
    while(T--) {
        scanf("%d %d",&n,&m);
        getchar();
        char ch;
        for(int i=0;i<n;++i) {
            for(int j=0;j<m;++j)
                a[i][j]=getchar()-'0';
            getchar();
        }
        int ed=n+m+1;
        int tot=0;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                tot+=a[i][j];
        int ans=min(tot,n*m-tot);
        for(int r=1;r<m;++r)
            if(r*n%m==0) {
                int c=n*r/m;
                if(abs(tot-n*r)<ans) {
                    solve.init();
                    for(int i=1;i<=n;++i)
                        solve.insert(0,i,r,0);
                    for(int j=1;j<=m;++j)
                        solve.insert(n+j,ed,c,0);
                    for(int i=0;i<n;++i)
                        for(int j=0;j<m;++j)
                            if(a[i][j])
                                solve.insert(i+1,n+j+1,1,-1);
							else 
								solve.insert(i+1,n+j+1,1,1);
                    ans=min(ans,solve.mincostmaxflow(0,ed,ed+1).first+tot);
                }
            }
        printf("Case %d: %d\n",kase++,ans);
    }
}
