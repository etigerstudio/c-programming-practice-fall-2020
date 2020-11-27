//
// Created by ALuier Bondar on 2020/11/27.
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

using namespace std;

string reverse(string &str) {
    int s = str.size();
    if (s == 0 || s == 1) return str;

    string tmp = str;
    for (int i = 0; i < s / 2; ++i) {
        swap(tmp[i], tmp[s - i - 1]);
    }
    return tmp;
}

int main() {
    int n;
    cin >> n;

    // Maximum cost
    const long long mc = numeric_limits<long long>::max();
    long long init[2] = {-1, -1};
    int *c = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    string *s = new string[n], *r = new string[n];
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        r[i] = reverse(s[i]);
    }

    // col 0: non-reversed; col 1: reversed;
    auto dp = new long long *[n];
    for (int i = 0; i < n; ++i) {
        dp[i] = init;
    }
    dp[0][0] = 0; dp[0][1] = c[0];
    for (int i = 1; i < n; ++i) {
        long long nn = mc, nr = mc, rn = mc, rr = mc;
        if (dp[i - 1][0] != mc && s[i - 1] < s[i]) {
            nn = dp[i - 1][0];
        }
        if (dp[i - 1][0] != mc && s[i - 1] < r[i]) {
            nr = dp[i - 1][0] + c[i];
        }
        if (dp[i - 1][1] != mc && r[i - 1] < s[i]) {
            rn = dp[i - 1][1];
        }
        if (dp[i - 1][1] != mc && r[i - 1] < r[i]) {
            rr = dp[i - 1][1] + c[i];
        }

        long long minn = min(nn, rn);
        long long minr = min(nr, rr);
        // Not feasible
        if (minn == mc && minr == mc)
        { cout << -1; return 0; }

        dp[i][0] = minn; dp[i][1] = minr;
    }

    cout << min(dp[n - 1][0], dp[n - 1][1]);
    return 0;
}