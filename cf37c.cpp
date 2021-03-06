#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_N = 1007;

typedef pair<int,int> pii;

int n;
int depth;
string path;
string ans[MAX_N];

void dfs(deque<pii>& v) {
	if (v.empty()) {
		return;
	} else if (v[0].first == depth) {
		ans[v[0].second] = path;
		v.pop_front();
		return;
	} else {
		++depth;
		path += '0';
		dfs(v);
		*path.rbegin() = '1';
		dfs(v);
		path.erase(path.end() - 1);
		--depth;
	}
}

int main() {
	deque<pii> v;
	scanf("%d", &n);
	v.resize(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &v[i].first);
		v[i].second = i;
	}
	sort(v.begin(), v.end());
	depth = 0;
	path = "";
	dfs(v);
	if (v.empty()) {
		puts("YES");
		for (int i = 0; i < n; ++i) {
			puts(ans[i].c_str());
		}
	} else {
		puts("NO");
	}
	return 0;
}

