#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

int n;
char s[10007];
crope ver[50007], now;

int main() {
	int d = 0, v = 0, p = 0, nowv = 0, c = 0;
	while (1 == scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			int typ;
			scanf("%d", &typ);
			now = ver[nowv];
			if(typ == 1) {
				scanf("%d%s", &p, s);
				p -= d;
				now.insert(p, s);
				ver[++nowv] = now;
			} else if(typ == 2) {
				scanf("%d%d", &p, &c);
				p -= d, c -= d;
				now.erase(p - 1, c);
				ver[++nowv] = now;
			} else {
				scanf("%d%d%d", &v, &p, &c);
				v -= d, p -= d, c -= d;
				crope cur = ver[v].substr(p - 1, c);
				int len = cur.size();
				int cnt = 0;
				for (int j = 0; j < len; ++j) {
					if (cur[j] == 'c') ++cnt;
				}
				d += cnt;
				printf("%s\n", cur.c_str());
			}
		}
	}
	return 0;
}
