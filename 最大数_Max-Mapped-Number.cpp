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

int main() {
    int n;
    cin >> n;

    int *d = new int[n];
    for (int i = 0; i < n; ++i) {
        // One digit at a time
        scanf("%1d", &d[i]);
    }

    int f[9];
    for (int j = 0; j < 9; ++j) {
        cin >> f[j];
    }

    // Is applying mapping?
    bool mapping = false;
    for (int k = 0; k < n; ++k) {
        // Trigger mapping
        if (f[d[k] - 1] > d[k]) {
            mapping = true;
            d[k] = f[d[k] - 1];
            continue;
        }

        // Maintain mapping
        if (f[d[k] - 1] == d[k] && mapping)
            continue;

        // Break mapping
        if (mapping) break;
    }

    for (int l = 0; l < n; ++l) {
        cout << d[l];
    }
}