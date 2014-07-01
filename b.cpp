#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 307;

int n, m;
int gcd[MAX_N][MAX_N];

int main() {
    for(int i = 1; i < MAX_N; ++i)
        for(int j = i; j < MAX_N; ++j)
            gcd[i][j] = __gcd(i, j);

	 while(2 == scanf("%d%d",&n,&m)) {
		 if (0 == n && 0 == m) 
		   break;
		 --n, --m;
         if (n > m) swap(n, m);
		 long long ans = 0;
         for(int x = 1; x <= n; ++x) {
             for(int y = x; y <= m; ++y)   if(gcd[x][y] <= 2) {
                 if(x == y) {
                     int tmp = (n - x + 1) * (m - y + 1);
                     if(gcd[x][y] == 1)  ans += tmp;
                     else ans -= tmp;
                 }
                 else {
                     int tmp = (n - x + 1) * (m - y + 1);
                     if(x <= m && y <= n)   tmp += (m- x + 1) * (n - y + 1);
                     if(gcd[x][y] == 1) ans += tmp;
                     else ans -= tmp;
					     
				 }
             }
         }
         ans *= 2;
         printf("%lld\n",ans);
     }
}
