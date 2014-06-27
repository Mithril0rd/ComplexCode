#include <cstdio> 
#include <algorithm> 
#include <cstring> 
const int Inf = (int)(1e9); 
const int N = 200 + 2; 
const int M = 100 + 2; 
struct node { 
    int val, pos; 
}; 
node chose[N][N]; 
struct tnode { 
    int i, pos; 
}; 
tnode pre[N][N]; 
int Cos[N][N], d[N][M]; 
int n, K; 
int ans[M], deep; 
void dfs(int i, int j) { 
    if (j == 0) return ; 
    dfs(pre[i][j].i, j - 1); 
    ans[deep ++] = pre[i][j].pos; 
} 
int getnum(){ 
    char ch; 
    while(((ch = getchar()) < '0' || ch > '9') && ch != '-'); 
    int num = ch - '0'; 
    while((ch = getchar()) >= '0' && ch <= '9') num = num * 10 + ch - '0'; 
    return num; 
} 
int main() { 
    int i, j, k, a; 
    while (2 == scanf("%d%d", &n, &K)) { 
        memset(Cos, 0, sizeof Cos); 
        for (i = 1; i <= n; ++i) { 
            a = getnum(); 
            for (j = 1; j <= n; ++j) 
                Cos[i][j] += Cos[i - 1][j] + abs(i - j) * a; 
        } 
        for (i = 1; i <= n; ++i) 
            for (j = i; j <= n; ++j) { 
                chose[i][j].val = Inf; 
                for (k = 1; k <= n; ++k) { 
                    a = Cos[j][k] - Cos[i - 1][k]; 
                    if (a < chose[i][j].val) { 
                        chose[i][j].val = a; 
                        chose[i][j].pos = k; 
                    } 
                } 
            } 
        for (i = 0; i <= n + 1; ++i) 
            for (j = 0; j <= K; ++j) { 
                d[i][j] = pre[i][j].pos = Inf; 
                pre[i][j].i = -1;  
            } 
        d[n + 1][0] = 0; 
        for (i = n + 1; i >= 2; --i)  
            for (j = 0; j < K; ++j) if (d[i][j] < Inf) 
                for (k = i - 1; k >= 1; --k) {  
                    if (d[k][j + 1] > d[i][j] + chose[k][i - 1].val) { 
                        d[k][j + 1] = d[i][j] + chose[k][i - 1].val; 
                        pre[k][j + 1].i = i;  
                        pre[k][j + 1].pos = chose[k][i - 1].pos; 
                    } else if (d[k][j + 1] == d[i][j] + chose[k][i - 1].val  
                        && pre[k][j + 1].pos > chose[k][i - 1].pos) 
                        pre[k][j + 1].pos = chose[k][i - 1].pos; 
                    else if (d[k][j + 1] == d[i][j] + chose[k][i - 1].val  
                        && pre[k][j + 1].pos == chose[k][i - 1].pos) 
                        pre[k][j + 1].i = i; 
                } 
        printf("%d\n", d[1][K]); 
        deep = 0; 
        dfs(1, K); 
        std::sort(ans, ans + deep); 
        for (i = 0; i < deep; ++i) { 
            if (i) putchar(' '); 
            if (i && ans[i] <= ans[i - 1]) ans[i] = ans[i - 1] + 1; 
            printf("%d", ans[i]); 
        } 
        puts(""); 
    } 
    return 0; 
} 
