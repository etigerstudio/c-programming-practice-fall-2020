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

using namespace std;

int n, *nums, bound;

void dfs(int d, int c, int l, int *ls) {
    if (d == n - 1) {
        cout << l;
        exit(0);
    }

    int cur = nums[d + 1];
    for (int i = 0; i < c; ++i) {
        if (ls[i] + cur <= l) {
            ls[i] += cur;
            dfs(d + 1, c, l, ls);
            ls[i] -= cur;
        }
    }
}

int main() {
    cin >> n;

    nums = new int[n];
    int sum = 0, maxlen = 0;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        maxlen = max(maxlen, nums[i]);
        sum += nums[i];
    }

    int *ls = new int[n];
    for (int i = maxlen; i <= sum; ++i) {
        if (sum % i != 0) {
            continue;
        }
        for (int j = 0; j < n; ++j) {
            ls[j] = 0;
        }
        dfs(0, sum / i, i, ls);
    }

    cout << 1;
    return 0;
}