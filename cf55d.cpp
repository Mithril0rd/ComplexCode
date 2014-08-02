#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
 
long long dp[19][50][252];
int dig[20];
int index[2521];

long long dfs(int pos, int lcm, int sum, bool U) {
        if (pos == -1) return sum % lcm == 0;
        if (!U && dp[pos][index[lcm]][sum] != -1) 
			return dp[pos][index[lcm]][sum];
        long long ret = 0;
        int end = U ? dig[pos] : 9;
        for (int i = 0 ; i <= end ; ++i) {
                int Nlcm = lcm;
                if (i > 0) Nlcm = lcm / __gcd(lcm, i) * i;
                int Nsum = sum * 10 + i;
                if (pos > 0) Nsum %= 252;
                ret += dfs(pos - 1, Nlcm, Nsum, U && i == end);
        }
        if (!U) dp[pos][index[lcm]][sum] = ret;
        return ret;
}

long long func(long long num) {
        int n = 0;
        while (num > 0) {
                dig[n++] = num % 10;
                num /= 10;
        }
        return dfs(n - 1, 1, 0, 1);
}
 
void init() {
        int sz = 0;
        for (int i = 1 ; i <= 2520 ; ++i) 
			if (2520 % i == 0) 
				index[i] = sz++;
        memset(dp , -1 , sizeof(dp));
}

int main() {
        init();
        int T;
        scanf("%d", &T);
        while (T-- > 0) {
                long long a , b;
                scanf("%I64d%I64d", &a, &b);
                long long ans = func(b) - func(a - 1);
                printf("%I64d\n", ans);		        
		}
        return 0;
}
