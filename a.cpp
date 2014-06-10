<<<<<<< HEAD
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <complex>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <map>
#include <set>
using namespace std;
//#pragma comment(linker,"/STACK:102400000,102400000")

int n, wantCycle;
int x[3001];
int c[3001];
int size[3001];

int nCycle()
{
	int ret = 0;
	memset(c, 0, sizeof(c));
	for(int i = 1; i <= n; i++)
		if(c[i] == 0)
		{
			ret ++;
			size[ret] = 0;
			int v = i;
			while(c[v] == 0)
			{
				c[v] = ret;
				v = x[v];
				size[ret] ++;
			}
		}
	return ret;
}

vector <int> A, B;

void increase()
{
	for(int i = 1; i <= n; i++)
		if(size[c[i]] != 1)
		{
			for(int j = 1; j <= n; j++)
				if(j != i && c[i] == c[j])
				{
					A.push_back(i);
					B.push_back(j);
					swap(x[i], x[j]);
					return;
				}
		}
}

void decrease()
{
	for(int j = 2; j <= n; j++)
		if(c[1] != c[j])
		{
			A.push_back(1);
			B.push_back(j);
			swap(x[1], x[j]);
			return;
		}
}



int MAIN()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> x[i];
	cin >> wantCycle;
	wantCycle = n - wantCycle;
	printf("%d\n", nCycle());
	while(true)
	{
		int cyc = nCycle();
		if(cyc == wantCycle)
			break;
		if(cyc < wantCycle)
			increase();
		else
			decrease();
	}
	cout << A.size() << endl;
	for(int i = 0; i < A.size(); i++)
	{
		cout << A[i] << " " << B[i] << (i == A.size()-1 ? "\n" : " ");
	}
	
	return 0;
}

int main()
{		
	ios :: sync_with_stdio(false);
	cout << fixed << setprecision(16);
	return MAIN();
}
=======
#include <cstdio>
#include <cstring>

const int MAX_N = 22;
const int MAX_S = 8007;

int n, m;
int mat[MAX_N][MAX_N];
int dp[MAX_N][MAX_S<<1];
int a[MAX_N], b[MAX_N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%d", b + i);
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			mat[i][j] = b[i] * a[j];
			if (i == 1) {
				if (mat[i][j] >= 0 && mat[i][j] < MAX_S) {
					dp[1][mat[i][j]] = 1;
				} else if (mat[i][j] < 0) {
					dp[1][MAX_S - mat[i][j]] = 1;
				}
			}
		}
	}
	for (int i = 2; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int k = 0; k < MAX_S; ++k) {
				if (mat[i][j] + k >= 0 && mat[i][j] + k < MAX_S) {
					dp[i][mat[i][j] + k] += dp[i - 1][k];
				} else if (mat[i][j] + k < 0) {
					dp[i][MAX_S - (mat[i][j] + k)] += dp[i - 1][k];
				}
			}
			for (int k = MAX_S; k < MAX_S * 2; ++k) {
				int t = MAX_S - k;
				if (mat[i][j] + t >= 0) 
					dp[i][mat[i][j] + t] += dp[i - 1][k];
				else if (mat[i][j] + t < 0)
					dp[i][MAX_S - (mat[i][j] + t)] += dp[i - 1][k];
			}
		}
	}
	int ans = dp[m][0];
	printf("%d\n", ans);
	return 0;
}
>>>>>>> dp/master
