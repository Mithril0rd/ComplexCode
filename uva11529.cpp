#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_N = 1207;
const double PI = acos(-1.);

struct Point {
	double x, y;
};

int n;
double ox[MAX_N<<1];
Point p[MAX_N];

long long C3(int n) {
	return (long long)n * (n - 1) / 2 * (n - 2) / 3;
}

long long C2(int n) {
	return (long long)n * (n - 1) / 2;

}

long long cal() {
	long long all = C3(n - 1);
	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		int cnt = 0;
		for (int j = 0; j < n; ++j) {
			if (j == i) 
			  continue;
			double at = atan2(p[j].y - p[i].y, p[j].x - p[i].x);
			ox[cnt++] = at;
		}
		sort(ox, ox + cnt); 
		int cnt1 = cnt;
		for (int j = 0; j < cnt1; ++j) {
			ox[cnt++] = ox[j] + 2 * PI;
		}
		int now = 0;
		long long count = 0;
		for (int j = 0; j < cnt1; ++j) {
			while (ox[now] < ox[j] + PI)
			  ++now;
			count += C2(now - j - 1);
		}
		ans += all - count;
	}
	return ans;
}

int main() {
	int cas = 0;
	while (1 == scanf("%d", &n)) {
		if (0 == n) 
		  break;
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf", &p[i].x, &p[i].y);
		}
		double ans = 1. * cal() / C3(n);
		printf("City %d: %.2f\n", ++cas, ans);
	}
	return 0;
}
