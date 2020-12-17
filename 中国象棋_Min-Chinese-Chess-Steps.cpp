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

int *cols;

int steps(int begin, int end, int height) {
    if (end < begin) {
        return 0;
    }

    int i = min_element(cols + begin, cols + end + 1) - cols;
    int l = steps(begin, i - 1, cols[i]);
    int r = steps(i + 1, end, cols[i]);
    return min(end - begin + 1, l + r - height + cols[i]);
}

int main() {
    int n;
    cin >> n;

    cols = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> cols[i];
    }

    cout << steps(0, n - 1, 0);
    return 0;
}