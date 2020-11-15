//
// Created by ALuier Bondar on 2020/11/15.
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

using namespace std;

int main(void) {
    int n;
    cin >> n;

    int min, max, num;
    cin >> num;
    max = min = num;
    auto m = unordered_map<int, int>();
    ++m[num];
    for (int i = 1; i < n; ++i) {
        cin >> num;
        ++m[num];
        min = num < min ? num : min;
        max = num > max ? num : max;
    }

    int* dp = new int[max - min + 1];
    for (int i = min; i <= max; ++i) {
        if (i == min) {
            dp[0] = m[min] * min;
            continue;
        }

        int l2 = m[i] * i;
        if (i > min + 1)
            l2 += dp[i - min - 2];
        int l1 = dp[i - min - 1];
        int cur = l1 + m[i] * i;
        int s = m[i] - m[i - 1];
        if (s > 0) {
            cur -= m[i - 1] * (i - 1);
        } else {
            cur -= (m[i - 1] - s) * (i - 1);
        }
        dp[i - min] = l2 > cur ? l2 : cur;
        dp[i - min] = dp[i - min] > l1 ? dp[i - min] : l1;
    }

    cout << dp[max - min];
}