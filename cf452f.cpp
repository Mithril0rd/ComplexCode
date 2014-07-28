#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 300007;

#define lson idx<<1
#define rson lson|1

struct Node {
	int l, r, sum;
	Node() {

	}
	Node(int _1, int _2, int _3) {
		l = _1, r = _2, sum = _3;
	}
};

int n;
Node seg[MAX_N<<2];

void build(int l, int r, int idx) {
	seg[idx] = Node(l, r, 0);
	if (l == r) 
	  return ;
	int mid = (l + r) >> 1;
	build(l, mid, lson), build(mid + 1, r, rson);
}

void up(int idx) {
	seg[idx].sum = seg[lson].sum + seg[rson].sum;
}

void update(int idx, int pos) {
	if (seg[idx].l == seg[idx].r) ++seg[idx].sum;
	else {
		int mid = (seg[idx].l + seg[idx].r) >> 1;
		if (pos <= mid) update(lson, pos);
		else update(rson, pos);
		up(idx);
	}
}

int query(int idx, int L, int R) {
	if (L <= seg[idx].l && seg[idx].r <= R) 
	  return seg[idx].sum;
	int mid = (seg[idx].l + seg[idx].r) >> 1;
	int res = 0;
	if (L <= mid) res += query(lson, L, R);
	if (R > mid) res += query(rson, L, R);
	return res;
}

int main() {
	scanf("%d", &n);
	build(1, n, 1);
	bool f = false;
	for (int i = 1; i <= n; ++i) {
		int val;
		scanf("%d", &val);
		if (f) continue;
		int chose = min(val - 1, n - val);
		if (chose == 0) update(1, val);
		else {
			int x = query(1, val - chose, val - 1);
			int y = query(1, val + 1, val + chose);
			if (x != y) {
				f = true;
				break;
			}
			update(1, val);
		}
	}
	if (f) puts("YES");
	else puts("NO");
	return 0;
}
