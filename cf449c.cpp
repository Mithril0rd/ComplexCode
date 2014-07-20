#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int MAX_N = int(1e5) + 10;
bool isP[MAX_N];
int minP[MAX_N];
int n;
vector<int> pa, pb;
bool done[MAX_N];

int main() {
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        isP[i] = true;
        minP[i] = i;
    }
    for (int i = 2; i <= n; ++i)
        if (isP[i])
            for (int j = i + i; j <= n; j += i)
                isP[j] = false, minP[j] = min(minP[j], i);

    for (int i = n; i >= 2; --i) {
        if (isP[i]) {
            vector<int> good, bad;
            for (int j = i; j <= n; j += i) {
                if (!done[j]) {
                    if (minP[j] == i) {
                        bad.push_back(j);
                    } else {
                        good.push_back(j);
                    }
                }
            }
            if ((good.size() + bad.size()) % 2 == 0) {
				vector<int> e = good;
                e.insert(e.end(), bad.begin(), bad.end());
                for (int i = 0; i + 1 < e.size(); i += 2) {
                    done[e[i]] = true;
                    done[e[i + 1]] = true;
                    pa.push_back(e[i]), pb.push_back(e[i + 1]);
                }
            } else {
                vector<int> e = bad;
                e.insert(e.end(), good.begin(), good.end());
                for (int i = 0; i + 1 < e.size(); i += 2) {
                    done[e[i]] = true;
                    done[e[i + 1]] = true;
                    pa.push_back(e[i]), pb.push_back(e[i + 1]);
                }
            }
        }
    }

    cout << pa.size() << endl;
    for (int i = 0; i < pa.size(); ++i) {
        cout << pa[i] << " " << pb[i] << endl;
    }
}
