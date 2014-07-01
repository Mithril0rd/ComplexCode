#include <cstdio>
#include <cstring>
#include <cmath>

long long cal(long long n) {
	if (n == -1) return -1;
	int cnt = 0;
	int digit[12] = {0};
	long long nn = n;
	while (nn > 0) {
		digit[cnt++] = nn % 10LL;
		nn /= 10LL;
	}

	long long ans = 0;
	long long pre = 0, tail = 0;
	for (int i = 0; i < cnt; ++i) {
		pre = n / (long long)pow(10., i + 1);
		if (digit[i] == 0) ans += (pre - 1) * (long long) pow(10., 1. * i) + (tail + 1);
		else ans += pre * (long long) pow(10., 1. * i);
		tail = tail + digit[i] * (long long) pow(10., 1. * i); 
	}
	return ans;
}

int main() {
	long long m, n;
	while (2 == scanf("%lld%lld", &m, &n)) {
		if (-1 == m && -1 == n)
		  break;
		long long ans = cal(n) - cal(m - 1);
		printf("%lld\n", ans);
	}
	return 0;
}
