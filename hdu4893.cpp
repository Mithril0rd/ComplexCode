#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

#define lson idx<<1
#define rson lson|1

const int MAX_N = 200007;

struct Node {
    int l, r;
    long long sum;
    int ok;
    Node () {
        
    }
    Node (int _l, int _r, long long _sum, int _ok) {
        l = _l, r = _r, sum = _sum, ok = _ok;
    }
}; 

int n, m;
Node seg[MAX_N << 1];
set<long long> fib;

struct Segment {
    void build(int l, int r, int idx) {
        seg[idx] = Node(l, r, 0, 0);
        if (l == r) return ;
        int mid = (l + r) >> 1;
        build(l, mid, lson); build(mid + 1, r, rson);
    }
    void up(int idx) {
        seg[idx].sum = seg[lson].sum + seg[rson].sum;
        seg[idx].ok = (seg[lson].ok & seg[rson].ok);
    }
    
    void update(int idx, ll pos, ll val) {
        if (pos < seg[idx].l  || pos > seg[idx].r) return ;
        if (seg[idx].l == seg[idx].r) {
            seg[idx].sum += val;
            if (fib.find(seg[idx].sum) != fib.end()) 
                seg[idx].ok = true;
            else 
                seg[idx].ok = false;
        } else {
            int mid = (seg[idx].l + seg[idx].r) >> 1;
            if (pos <= mid) update(lson, pos, val);
            else update(rson, pos, val);
            up(idx); 
        }
        
    }

    void change(int idx, ll l, ll r) {
        if (r < seg[idx].l || l > seg[idx].r) return ;
        if (seg[idx].ok) return ;
        if (seg[idx].l == seg[idx].r) {
            if (fib.find(seg[idx].sum) != fib.end()) 
                return ;
            set<long long>::iterator it = fib.lower_bound(seg[idx].sum); 
            long long r = *it; --it; long long l = *it; 
        //    printf("qqqqq    %lld %lld %lld %lld\n", (long long) idx, seg[idx].sum, l, r);
            if (abs(seg[idx].sum - l) <= abs(seg[idx].sum - r)) {
                seg[idx].sum -= abs(seg[idx].sum - l);
            } else seg[idx].sum += abs(seg[idx].sum - r);
        //    printf("qqqqq2    %lld %lld %lld %lld\n", (long long) idx, seg[idx].sum, l, r);
            seg[idx].ok = true;
        } else {
            int mid = (seg[idx].l + seg[idx].r) >> 1;
            if (r <= mid) change(lson, l, r);
            else if (l > mid) change(rson, l, r);
            else {
                change(lson, l, mid), change(rson, mid + 1, r);
            }
            up(idx);
        }
    }

    long long query(int idx, ll l, ll r) {
        if (r < seg[idx].l || l > seg[idx].r) return 0LL;
        if (seg[idx].l == l && seg[idx].r == r) {
            return seg[idx].sum;    
        } else {
            int mid = (seg[idx].l + seg[idx].r) >> 1;
            long long ans = 0;
            if (r <= mid)  ans = query(lson, l, r);
            else if (l > mid) ans = query(rson, l, r);
            else ans = query(lson, l, mid) + query(rson, mid + 1, r);
            up(idx);
            return ans;
        }
    }
};

long long f[100];

int main() {
    f[0] = f[1] = 1;
    fib.insert(1);
    for (int i = 2; i < 90; ++i) {
        f[i] = f[i - 1] + f[i - 2];
    //    printf("%d\n", i);
        if (f[i] < 0) break;
        fib.insert(f[i]);
    }
    while (2 == scanf("%d%d", &n, &m)) {
        Segment ans;
        for (int i = 0; i < n + 2; ++i) {
            seg[i] = Node(0, 0, 0, 0);
        }
        ans.build(1, n, 1);
        for (int i = 0; i < m; ++i) {
            ll typ, l, r;
            scanf("%I64d%I64d%I64d", &typ, &l, &r);
            if (1 == typ) ans.update(1, l, r);
            else if (2 == typ) {
                long long q = ans.query(1, l, r);
                printf("%I64d\n", q);
            }
            else ans.change(1, l, r); 
        }
    }
    return 0;
} 
