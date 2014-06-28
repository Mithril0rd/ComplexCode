#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const long long MAX_N = 1000007;

struct node {
	int a, b, c;
	bool operator < (const node &rhs) const {
		return c < rhs.c;
	}
};

struct node2 {
	int a, b, c;
	bool operator < (const node2 &rhs) const {
		return a != rhs.a ? a < rhs.a : b != rhs.b ? b < rhs.b : c < rhs.c;
	}
};
int n, l, r;
vector<node> g;
vector<node2> ans;

int main() {
	g.push_back((node){0, 0, 0});
	for (int x = 1; x < 1007; ++x) {
		for (int y = x + 1; y < 1007; ++y) {
			int a = 2 * x * y;
			int c = x * x + y * y;
			int b = y * y - x * x;
			if (a > b) swap(a, b);
			if (__gcd(a, __gcd(b, c)) == 1 && a * a + b * b == c * c) {
				g.push_back((node) {a, b, c});
			}
		}
	}
	sort(g.begin(), g.end());
	while (3 == scanf("%d%d%d", &n, &l, &r)) {
		int len = g.size();
		ans.push_back((node2){0, 0, 0});
		for (int i = 1; i < len; ++i) {
			if (g[i].c <= n) 
			  ans.push_back((node2){g[i].a, g[i].b, g[i].c});
			else break;
		}
		sort(ans.begin(), ans.end());
		int limit = min((int)ans.size() - 1, r);
		printf("%d\n", max(0, limit - l + 1));
		int cas = 0;
		for (int i = l; i <= limit; ++i) {
			printf("Case: %d a=%d,b=%d,c=%d\n", ++cas, ans[i].a, ans[i].b, ans[i].c);
		}
	}
	return 0;
}
