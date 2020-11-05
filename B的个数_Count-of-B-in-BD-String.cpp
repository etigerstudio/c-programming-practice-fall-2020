//
// Created by ALuier Bondar on 2020/11/5.
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

using namespace std;

#define LEN 60
typedef unsigned long long ll;
ll len[LEN];
ll b[LEN];

void init() {
    len[0] = 1;
    b[0] = 1;
    for (int i = 1; i < LEN; i++) {
        len[i] = 2 * len[i - 1] + 1;
        b[i] = len[i - 1] + 1;
    }
}

ll bCount(ll l) {
    if (l == 0) return 0;  // Baseline
    if (l == 1) return 1;
    for (int i = 1; i < LEN; i ++) {
        if (l == len[i]) {
            return b[i];
        } else if (l < len[i]) { // Hit
            ll rhs = l - len[i - 1] - 1;
            return bCount(len[i - 1] - rhs) + 1 + rhs;
        }
    }

    return -1;
}

int main() {
    init();

    int n;
    cin >> n;

    while(n--) {
        int l, r;
        cin >> l >> r;
        cout << bCount(r) - bCount(l - 1) << endl;
    }

    return 0;
}
