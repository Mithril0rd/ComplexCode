#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAX_A = 27;
const int MAX_N = 207;
const int MAX_L = 1007;
const int MOD = (int)1E9 + 7;

char str[MAX_L], temp[MAX_N];
long long dp[MAX_L];

struct node {
	node *next[MAX_A];
	int val;
};
node *root;

node *addnode() {
	node *p = (node *) malloc(sizeof(node));
	p->val = 0;
	for (int i = 0; i < MAX_A; ++i)
	  p->next[i] = NULL;
	return p;
}

void del(node *p) {
	for (int i = 0; i < MAX_A; ++i)
	  if (p->next[i] != NULL) 
		del(p->next[i]);
	free(p);
}

void insert(char *s) {
	node *p = root;
	int i = 0;
	while (s[i]) { 
		int q = s[i++] - 'A';
		if (p->next[q] == NULL) 
			p->next[q] = addnode(); 
		p = p->next[q];
	}
	++p->val;
}

void query() {
	node *p = root;
	int i = 0;
	while (str[i]) {
		int q = str[i] - 'A';
		if (p->next[q] == NULL)
		  break;
		p = p->next[q];
		dp[i] = p->val;
		++i;
	}
}

long long tp[MAX_L];

void update(char *s, int idx) {
	memset(tp, 0, sizeof tp);
	node *p = root;
	int i = 0;
	long long tot = 0;
	while (s[i]) {
		int q = s[i] - 'A';
		if (p->next[q] == NULL)
			break;
		p = p->next[q];
		if (p->val > 0) 
		  tp[i + idx] = (tot * p->val) % MOD;
		tot = (tot + dp[i + idx]) % MOD;
		++i;
	}
	for (int j = idx; j <= idx + i; ++j) 
	  dp[j] = (tp[j] + dp[j]) % MOD;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T-- > 0) {	
		scanf("%s", str);
		int n;
		scanf("%d", &n);
		root = addnode();
		for (int i = 1; i <= n; ++i) {
			scanf("%s", temp);
			if (strlen(temp) == 1) 
			  continue;
			insert(temp);
		}
		memset(dp, 0, sizeof dp);
		query();
		for (int i = 1; str[i]; ++i) 
		  update(str + i, i);
		long long ans = dp[strlen(str) - 1];
		printf("%lld\n", ans);
		del(root);
	}
	return 0;
}
