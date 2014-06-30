#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 1007;

struct P {
	int s, t;
	bool operator < (const P &rhs) const {
		return t < rhs.t;
	}
};

int n, ans[MAX_N];
P p[MAX_N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &p[i].s, &p[i].t);
		if (p[i].s > p[i].t) swap(p[i].s, p[i].t);
	}
	sort(p + 1, p + 1 + n);
	int Max = - (int) 1e9 + 7, cnt = 0;
	for (int i = 1; i <= n; ++i) {
		printf("%d %d\n", p[i].s, p[i].t);
	}
	for (int i = 1; i <= n; ++i) {
		if (p[i].s > Max) {
			Max = p[i].t;
			ans[cnt++] = p[i].t;
		}
	}
	printf("%d\n", cnt);
	for (int i = 0; i < cnt; ++i) {
		if (i == 0) printf("%d", ans[i]);
		else printf(" %d", ans[i]);
	}
	puts("");
	return 0;
}
