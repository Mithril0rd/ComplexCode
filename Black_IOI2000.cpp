#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

#define MAX 105

const int INF = (1<<29);

int n, K;
int val[3][MAX], f[3][MAX];
int dp[12][MAX][5];
int result;

inline int min(int a, int b) {
 return a < b ? a : b;
}

int getLoss(int i, int j) //0:上下不用, 1:上用, 2:下用, 3:灭火器覆盖最少1个小矩形, 4:覆盖至少2个矩形
{
 if(j == 0) return f[1][i]+f[2][i];
 else if(j == 1) return val[1][i]+f[2][i];
 else if(j == 2) return val[2][i]+f[1][i];
 else return val[1][i]+val[2][i];
}

int DP(int k, int i, int j) {
 if(dp[k][i][j] != -1) return dp[k][i][j];
 if(i == n) return 0;

 int ans = INF, temp;
 int nextk;
 for(int p = 0; p <= 3; ++p) {
  if(p == 3 && (j == 1 || j == 2 || j == 4)) p = 4;

  if( p == 0 || j == p || j == 4 ) nextk = k;
  else nextk = k+1;
  if(nextk <= K) temp = DP(nextk, i+1, p)+getLoss(i+1, p);
  else continue;
  ans = min(ans, temp);
 }
 return dp[k][i][j] = ans;
}

int main() {
 int i, j;
 while( scanf("%d %d", &n, &K) != EOF ) {
  for(i = 1; i <= 2; ++i) {
   for(j = 1; j <= n; ++j)
    scanf("%d", &val[i][j]);
  }

  for(i = 1; i <= 2; ++i) {
   for(j = 1; j <= n; ++j)
    scanf("%d", &f[i][j]);
  }

  memset(dp, -1, sizeof(dp));
  result = DP(0, 0, 0);
  printf("%d\n", result);
 }
 return 0;
}
