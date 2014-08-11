#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 50007;

char s[MAX_N], str[MAX_N << 1];
int p[MAX_N << 1];

void getFail() {
	int j = 0;
	p[1] = 0;
	int m = (int) strlen(str + 1);
	memset(p, 0, sizeof p);
	for (int i = 2; i <= m; ++i) {
		while (j > 0 && str[j + 1] != str[i]) j = p[j];
		if (str[j + 1] == str[i]) ++j;
		p[i] = j;
	}
	for (int i = 1; i <= p[m]; ++i)
	  putchar(str[i]);
	if (p[m]) printf(" %d\n", p[m]);
	else puts("0");
}

int main() {
	while (1 == scanf("%s", s)) {	
		int j = 1;
		for (int i = 0; s[i]; ++i)
			str[j++] = s[i];
		str[j++] = '*';
		scanf("%s", s);
		for (int i = 0; s[i]; ++i)
			str[j++] = s[i];
		str[j] = '\0';
		getFail();
	}
	return 0;
}
