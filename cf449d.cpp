#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MOD = 1000000007;
const int N = (1 << 20) + 9;

int c[N] , n , a[N] , p[N] , s[N];

int main() {
    cin >> n;
    for (int i = 0 ; i < n ; i ++) {
        cin >> a[i];
        c[a[i]] ++;
    }
    p[0] = 1;
    for (int i = 1 ; i < N ; i ++) {
        p[i] = p[i - 1] * 2 % MOD;
        s[i] = s[i >> 1] + (i & 1);
    }
    for (int i = 0 ; i < 20 ; i ++) {
        for (int j = 0 ; j < (1 << 20) ; j ++) {
            if(j & (1 << i))
				c[j - (1 << i)] += c[j];
        }
    }

    LL ans = p[n];
    for (int i = 1 ; i < (1 << 20) ; i ++) {
        if (s[i] & 1) ans -= p[c[i]];
        else ans += p[c[i]];
    }
    cout << (ans % MOD + MOD) % MOD << endl;
    return 0;
}
