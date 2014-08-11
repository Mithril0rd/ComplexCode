#include <cstdio>
#include <cstring>

const int MAX_N = 100007;

char str[MAX_N << 1], s[MAX_N];
int p[MAX_N];

void getFail() {
	int j = 0;
	p[1] = 0;
	int m = (int) strlen(str);
	for (int i = 2; i <= m; ++i) {
		while (j > 0 && s[j + 1] != s[i]) j = p[j];
		if (s[j + 1] == s[i]) ++j;
		p[i] = j;
	}
}

int main() {
	while (1 == scanf("%s", s)) {
		int j = 1; 
		for (int i = 0; s[i]; ++i)
		  str[j++] = s[i];
		for (int i = 0; s[i]; ++i)
		  str[j++] = s[i];
		str[j] = '\0';
		scanf("%s", s + 1);
		getFail();
		bool f = false;
		int k = 0, len = (int) strlen(s + 1);
		for (int i = 1; i < j; ++i) {
			while (k > 0 && s[k + 1] != str[i]) k = p[k];
			if (s[k + 1] == str[i]) ++k;
			if (k == len) {
				f = true;
				break;
			}
		}
		if (f) puts("yes");
		else puts("no");
	}
	return 0;
}
