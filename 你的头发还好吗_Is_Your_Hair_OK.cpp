//
// Created by ALuier Bondar on 2020/12/31.
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

tuple<int, int> *data;
int n, m, maxXSum = -1;

bool gt(const tuple<int, int> &t1, const tuple<int, int> &t2) {
    return get<0>(t1) > get<0>(t2);
}

void dfs(int i, int xSum, int ySum, int xRemaining) {
    if (ySum != 0 && xSum / ySum == m && xSum % ySum == 0) {
        maxXSum = max(maxXSum, xSum); // Update solution/bound
    }
    if (i == n || xSum + xRemaining <= maxXSum) { // Bounding
        return;
    }

    int x = get<0>(data[i]);
    int y = get<1>(data[i]);
    dfs(i + 1, xSum + x, ySum + y, xRemaining - x);
    dfs(i + 1, xSum, ySum, xRemaining - x);
}

int main() {
    cin >> n >> m;

    data = new tuple<int, int>[n];
    int *xs = new int[n], *ys = new int[n];
    int xSum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> xs[i];
        xSum += xs[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> ys[i];
    }
    for (int i = 0; i < n; ++i) {
        data[i] = make_tuple(xs[i], ys[i]);
    }

    sort(data, data + n, gt);
    dfs(0, 0, 0, xSum);

    cout << maxXSum;
    return 0;
}