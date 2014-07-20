#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int n, m, k;
	long long ans = -1;
	cin >> n >> m >> k;
	if(k > n + m -2)
		ans = -1;
	else {
		int mx = max(n - 1, m - 1);
		int mn = min(n - 1, m - 1);
		if(k > mx)
			ans = (mn + 1) / (k - mx + 1);
		else
			ans = max(1ll * n / (k + 1) * m, 1ll * m / (k + 1) * n);
	}
	cout << ans << endl;
	return 0;
}
