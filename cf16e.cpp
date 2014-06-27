#include <bits/stdc++.h>
using namespace std;

double dp[1 << 18];

int main() {
    double a[35][35];
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            scanf("%lf",&a[i][j]);
    dp[(1 << n) - 1] = 1;
    int re[25];
    for(int i = (1 << n) - 1; i > 0; i --) {
        if(i == (i & (-i))) continue;
        int c = 0;
        for(int j = 0; j < n; j ++) {
            if(i & (1 << j)) re[c++] = j;
        }
        double p = 2.0 / c / (c - 1);
        for(int j = 0; j < c; j ++)
            for(int k = 0; k < c; k ++)
                if(i == j) continue;
                else dp[i ^ (1 << re[j])] += dp[i] * p * a[re[k]][re[j]];
    }
    for(int i = 0; i < n; i ++) 
	  printf("%.6f ",dp[1 << i]);
    puts(""); 
	return 0;
}
