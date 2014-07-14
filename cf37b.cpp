#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int,int> pii;

const int MAX_N = 1007;

struct Node {
	int Pow, Dmg, idx;
	Node() {

	}
	Node(int _i, int _j, int _k) {
		Pow = _i, Dmg = _j, idx = _k;
	}
	bool operator < (const Node &rhs)  const {
		return Pow != rhs.Pow ? Pow < rhs.Pow : Dmg < rhs.Dmg;
	}
};

int N, Max, Reg;
Node scroll[MAX_N];
vector<pii> ans;

int main() {
	scanf("%d%d%d", &N, &Max, &Reg);
	for (int i = 1; i <= N; ++i) {
		scanf("%d%d", &scroll[i].Pow, &scroll[i].Dmg);
		scroll[i].idx = i;
	}
	sort(scroll + 1, scroll + 1 + N);
	priority_queue<pii> que;

	int Time = 0, health = Max, damage = 0;
	for (int i = 0; i < 100000; ++i) {
		if (health <= 0) break;
		Time = i + 1;
		while (N > 0 && health <= Max * scroll[N].Pow / 100) {
			que.push(make_pair(scroll[N].Dmg, scroll[N].idx));
			--N;
		}
		if (!que.empty()) {
			damage += que.top().first;
			ans.push_back(make_pair(i, que.top().second));
			que.pop();
		}
		health = min(Max, health - damage + Reg);
	}
	if (health > 0) {
		puts("NO");
	} else {
		puts("YES");
		printf("%d %d\n", Time, (int)ans.size());
		for (int i = 0; i < (int)ans.size(); ++i) {
			printf("%d %d\n", ans[i].first, ans[i].second);
		}
	}
	return 0;
}
