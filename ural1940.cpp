#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int N = 400;

int A, B, K;
std::vector<int> prime;
ll NN, ans;
bool vis[N], vis1[N];

void prepare() {
	memset(vis, 0, sizeof vis);
	prime.clear();
	vis[0] = vis[1] = true;
	for (int i = 2; i <= K; ++i)
		if (!vis[i]) {
			prime.push_back(i);
			for (int j = i * i; j <= K; j += i)
				vis[j] = true;
		}
}

void dfs(int idx, ll get, int f) {
	ans += NN / get * f;
//	printf("%lld qqq\n", NN / get * f);
	if (get < 300 && !vis1[get])
	  ++ans;//, printf("%lld here\n", get);
	for (int i = idx + 1; i < prime.size(); ++i) {
		if (get * prime[i] > NN) 
		  return ;
		dfs(i, get * prime[i], f * -1);
	}
}

int main() {
	vis1[0] = vis1[1] = true;
	for (int i = 2; i < 301; ++i) {
		if (!vis1[i]) {
			vis1[i] = false;
			for (int j = i * i; j <= 301; j += i) {
				vis1[j] = true;
			}
		}
	}

	std::cin >> A >> B >> K;
	++K;
	prepare();
	ans = 0;
	NN = A;
	dfs(-1, 1, 1);
	ll pre = ans;
	NN = A + B;
	ans = 0; puts("");
	dfs(-1, 1, 1);
//	ans -= pre;
	printf("ans1 %lld ans2 %lld ans3 %lld\n", pre, ans, ans - pre);
//	puts("ans");
//	std::cout << ans << std::endl;
	return 0;
}
