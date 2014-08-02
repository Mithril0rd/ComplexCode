#include <cstdio>
#include <cstring>

const int INF = (int)1e9;
const int MAX_N = 100007;

struct Point {
    double x ,y;
    Point() {
    	
    }
    Point(double _x, double _y) {
    	x = _x, y = _y;
    }
};

int n;
Point pt[MAX_N << 1];

double cross(Point A, Point B, Point O) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

int main() {
	scanf("%d", &n);
    for(int i = 0 ; i < n ; ++i) {
    	double x, y;
    	scanf("%lf%lf", &x, &y);
    	pt[i] = pt[i + n] = Point(x, y);
    }
    int t;
    scanf("%d", &t);
    while(t-- > 0) {
        Point xy;
        double x, y;
        scanf("%lf%lf", &x, &y);
        xy = Point(x, y);
        bool flag = false;
        for(int i = 0 ; i < n ; ++i) {
            if(cross(pt[i + 1], xy,  pt[i]) >= 0) {
                flag = true;
                break;
            }
        }
        if(flag) {
            puts("0");
            continue;
        }
		long long ans = (long long) n * (n - 1) * (n - 2) / 6;
        for(int i = 0, j = 2; i < n; ++i) {
            while(cross(xy, pt[j], pt[i]) > 0) ++j;
            ans -= (long long) (j - i - 1) * (j - i - 2) / 2; 
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
