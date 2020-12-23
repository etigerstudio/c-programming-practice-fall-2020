//
// Created by ALuier Bondar on 2020/12/23.
//

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <limits>
#include <iomanip>
#include <cmath>
#include <queue>
#include <stack>
#include <cfloat>
#include <string>
#include <cstdlib>

using namespace std;

int n, **dist, dmax = 0;
int *l, *r;

void dfs(int d, int lc, int rc) {
    if (d == n) {
        int dcur = 0;
        for (int i = 0; i < lc; ++i) {
            for (int j = 0; j < rc; ++j) {
                dcur += dist[l[i]][r[j]];
            }
        }
        dmax = max(dmax, dcur);
        return;
    }

    l[lc] = d;
    dfs(d + 1, lc + 1, rc);

    r[rc] = d;
    dfs(d + 1, lc, rc + 1);
}

int main() {
    cin >> n;

    dist = new int *[n * n];
    for (int i = 0; i < n; ++i) {
        dist[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            int tmp;
            cin >> tmp;
            dist[i][j] = tmp;
        }
    }

    l = new int[n]{0};
    r = new int[n]{0};
    dfs(0, 0, 0);

    cout << dmax;
    return 0;
}