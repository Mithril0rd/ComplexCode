#include <cstdio>
#include <cstring>

const int MAX_N = 100007;

int n;
long long  h[MAX_N], l[MAX_N], r[MAX_N];

int main() {
	while (1 == scanf("%d", &n)) {
		if (0 == n)
		  break;
		for (int i = 1; i <= n; ++i) {
			scanf("%I64d", &h[i]);
		}
		for (int i = 1; i <= n; ++i) {
			l[i] = i - 1;
			r[i] = i + 1;
		} 		
		for (int i = 1; i <= n; ++i) {
			while (h[l[i]] >= h[i] && l[i] > 0)
			  l[i] = l[l[i]];
		} 	
		for (int i = n; i >= 1; --i) {
			while (h[r[i]] >= h[i] && r[i] <= n)
			  r[i] = r[r[i]];
		}
		long long ans = 0; 	
		for (int i = 1; i <= n; ++i) {
	//      printf("%d %d %d\n", i, l[i], r[i]);
			if (h[i] * (r[i] - l[i] - 1) > ans) {
			//	printf("%d\n", i);
				ans = h[i] * (r[i] - l[i] - 1);
			}
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
