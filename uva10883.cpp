#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_N = 50007;
const double EPS = 1e-8;

double a[MAX_N], _lg[MAX_N];

int dcmp(double x) {
	if (fabs(x) < EPS) 
	  return 0;
	return x > EPS ? 1 : -1;
}

int main() {
    int cas = 0;
    int T; 
	scanf("%d", &T);
    while(T-- > 0)  {
		int n;
		scanf("%d", &n);
		--n;
		for (int i = 0; i <= n; ++i) {
			scanf("%lf", &a[i]);
		}
		_lg[0] = 0;
		for (int i = 1; i <= n; ++i) {
			_lg[i] = _lg[i - 1] + log10(n - i + 1) - log10(i);
		}
		double ans = 0;
		double end = log10(2) * n;
		for (int i = 0; i <= n; ++i) {
			if (dcmp(a[i]) < 0) ans -= pow(10, _lg[i] - end + log10(-a[i]));
			else if (dcmp(a[i]) > 0) ans += pow(10, _lg[i] - end + log10(a[i]));
		}
		printf("Case #%d: %.3f\n" , ++cas, ans);
    }
    return 0 ;
}

