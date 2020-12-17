//
// Created by ALuier Bondar on 2020/12/11.
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

int main() {
    int n;
    cin >> n;

    if (n == 1 || n % 2 == 0) {
        cout << -1;
        return 0;
    }

    int *s = new int[n + 1];
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }

    int sum = 0;
    for (int i = (n - 1) / 2; i >= 1; --i) {
        int imax = max(s[i * 2], s[i * 2 + 1]);
        if (imax > s[i])
            s[i] = 0;
        else
            s[i] -= imax;
        sum += imax;
    }
    sum += s[1];

    cout << sum;
    return 0;
}