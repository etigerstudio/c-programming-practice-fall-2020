//
// Created by ALuier Bondar on 2020/12/19.
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

int nums[5][5] = {};
set<int> ans;

void dfs(int r, int c, int d, int n) {
    if (d > 5) return;
    if (d == 5) ans.insert(n);

    if (r > 0) dfs(r - 1, c, d + 1, n * 10 + nums[r - 1][c]);
    if (r < 4) dfs(r + 1, c, d + 1, n * 10 + nums[r + 1][c]);
    if (c > 0) dfs(r, c - 1, d + 1, n * 10 + nums[r][c - 1]);
    if (c < 4) dfs(r, c + 1, d + 1, n * 10 + nums[r][c + 1]);
}

int main() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> nums[i][j];
        }
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            dfs(i, j, 0, nums[i][j]);
        }
    }

    cout << ans.size();
    return 0;
}