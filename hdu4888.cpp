#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_N = 807;
const int MAX_E = MAX_N * MAX_N * 5;
const int INF = 0x3f3f3f3f;

struct Edge {
    int v, nxt;
    long long cap;
    Edge() {

    }
    Edge(int _v, int _nxt, long long _cap) {
        v = _v, nxt = _nxt, cap = _cap;
    }
};

Edge G[MAX_E];
int edgecnt, head[MAX_N];
int gap[MAX_N], d[MAX_N];

struct Isap {
    int n, s, t;
    void init(int n, int s, int t) {
        this->n = n, this->s = s, this->t = t;
        edgecnt = 0;
        memset(head, -1, sizeof head);
    }
    void addedge(int u, int v, long long cap) {
        G[edgecnt] = Edge(v, head[u], cap);
        head[u] = edgecnt++;
        G[edgecnt] = Edge(u, head[v], 0);
        head[v] = edgecnt++;
    }
    long long dfs(int u, long long tot) {
        if (u == t) return tot;
        int minh = n - 1;
        long long leave = tot;
        for (int i = head[u]; ~i && leave; i = G[i].nxt) {
            int v = G[i].v;
            if (G[i].cap > 0) {
                if (d[v] + 1 == d[u]) {
                    long long c = dfs(v, min(leave, G[i].cap));
                    G[i].cap -= c;
                    G[i ^ 1].cap += c;
                    leave -= c;
                    if (d[s] >= n) 
                        return tot - leave;
                }
                minh = min(minh, d[v]);
            }
        }
        if (leave == tot) {
            --gap[d[u]];
            if (gap[d[u]] == 0) d[s] = n;
            d[u] = minh + 1;
            ++gap[d[u]];
        }
        return tot - leave;
    }
    long long maxFlow() {
        long long ret = 0;
        memset(gap, 0, sizeof gap);
        memset(d, 0, sizeof d);
        gap[0] = n;
        while (d[s] < n) {
            ret += dfs(s, INF);
        }
        return ret;
    }
};
 
int n, m, k;
int mat[MAX_N][MAX_N];
int c[MAX_N][MAX_N]; // 当前行时，前面是否有在i列可增j列可减的状态 

int main() {
    while (3 == scanf("%d %d %d", &n, &m, &k)) {
        Isap ans;
        ans.init(n + m + 2, 0, n + m + 1);
        int s = 0, t = n + m + 1;
        long long sum1 = 0, sum2 = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                ans.addedge(i, n + j, k);
            }
        }
        for (int i = 1; i <= n; ++i) {
            int rowSum = 0;
            scanf("%d", &rowSum);
            sum1 += rowSum;
            ans.addedge(0, i, rowSum);    
        }
        for (int i = 1; i <= m; ++i) {
            int colSum = 0;
            scanf("%d", &colSum);
            sum2 += colSum;
            ans.addedge(n + i, t, colSum);
        }       
        int q = ans.maxFlow();
        if (sum1 != sum2 || q != sum1) puts("Impossible");
        else {
            int edge = 0;
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j, edge += 2) {
                    mat[i][j] = G[edge ^ 1].cap;
                }
            }
            memset(c, false, sizeof c);
            bool f = false;
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    for (int l = j + 1; l <= m; ++l) {
                        bool f1 = false, f2 = false;
                        if (mat[i][j] != k && mat[i][l] != 0) {// column j could add, column l could dec 
                            if (c[l][j]) {
                                l = m + 1, j = m + 1, i = n + 1;
                                f = true;
                            }
                            f1 = true;
                        }
                        if (mat[i][j] != 0 && mat[i][l] != k) {// column l could add, column j could dec
                            if (c[j][l]) {
                                l = m + 1, j = m + 1, i = n + 1;
                                f = true;
                            }
                            f2 = true;
                        }
                        if (f1) c[j][l] = true;
                        if (f2) c[l][j] = true;
                    }
                }
            }
            if (f) puts("Not Unique");
            else {
                puts("Unique");
                for (int i = 1; i <= n; ++i) {
                    for (int j = 1; j <= m; ++j) {
                        if (j == 1) printf("%d", mat[i][j]);
                        else printf(" %d", mat[i][j]);
                    }
                    puts("");
                }
            } 
        }
    } 
    return 0;
}
