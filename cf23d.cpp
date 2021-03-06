#include <cstdio>
#include <cstring>
#include <cmath>

const double EPS = 1e-10;

struct Point {
	double x , y;
	Point () {}
	Point (double _x , double _y) {
		x = _x;
		y = _y;
	}
	double sqr(double d) {
		return d * d;
	}
	double dist(Point a) {
		return sqr (x - a.x) + sqr (y - a.y);
	}
	Point sym(Point a) {
		return  Point (x * 2 - a.x , y * 2 - a.y);
	}
	Point circumcenter(Point a , Point b) {
		double a1 = b.x - a.x , b1 = b.y - a.y , c1= (a1 * a1 + b1 * b1) / 2.0;
		double a2 = x - a.x , b2 = y - a.y , c2 = (a2 * a2 + b2 * b2) / 2.0;
		double d = a1 * b2 - a2 * b1;
		return Point (a.x + (c1 * b2 - c2 * b1) / d , a.y + (a1 * c2 - a2 * c1) / d);
	}
};

double xmul (Point p , Point p1 , Point p2) {
	return (p.x - p1.x) * (p.y - p2.y) - (p.y - p1.y) * (p.x - p2.x);
}

bool equal(double a , double b) {
	return fabs(a - b) < EPS;
} 

bool check (Point a , Point b , Point c , Point d) {
	double t1 = xmul(a , b , c) , t2 = xmul(b , c , d) , t3 = xmul(c , d , a) , t4 = xmul (d , a , b);
	if (t1 * t2 <= 1e-5 || t2 * t3 <= 1e-5 || t3 * t4 <= 1e-5 || t4 * t1 <= 1e-5) return false;
	return true;
}

bool solve(Point k , Point l , Point m) {
	if (xmul(k , l , m) == 0) return false;
	Point b = k.circumcenter(l.sym(m) , l) , a = k.sym(b), c = l.sym(b), d = m.sym(c);
	if (!equal(a.dist(b) , b.dist(c)) || !equal(b.dist(c), c.dist(d))) return false;		
	if (!check(a , b , c , d)) return false;
	puts("YES");
	printf("%.9f %.9f %.9f %.9f %.9f %.9f %.9f %.9f\n", a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y);
	return true;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		Point k = Point(x, y);
		scanf("%lf%lf", &x, &y);
		Point l = Point(x, y);
		scanf("%lf%lf", &x, &y);
		Point m = Point(x, y);
		if (solve(k, m, l)) continue; 
		if (solve(k, l, m)) continue; 
		if (solve(l, k, m)) continue;  
		if (solve(l, m, k)) continue;  	
		if (solve(m, k, l)) continue;
		if (solve(m, l, k)) continue;
		puts("NO"); puts("");
	}
	return 0;
}

