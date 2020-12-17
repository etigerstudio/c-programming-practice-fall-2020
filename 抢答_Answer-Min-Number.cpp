//
// Created by ALuier Bondar on 2020/12/17.
//

<!-- Backtracking with Pruning (Timeout) -->

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

int lower, upper;
int imax;
string number, nmin;

bool valid(const string &n) {
    int c4 = 0, c7 = 0;

    if (n.size() % 2 != 0) {
        return false;
    }

    for (int i = 0; i < n.size(); ++i) {
        switch (n[i]) {
            case '4':
                ++c4;
                break;
            case '7':
                ++c7;
                break;
            default:
                return false;
        }
    }

    if (c4 != c7)
        return false;

    return true;
}

bool gte(const string &n1, const string &n2) {
    for (int i = 0; i < n1.size(); ++i) {
        if (n1[i] > n2[i]) {
            return true;
        } else if (n1[i] < n2[i]) {
            return false;
        }
    }
    return true;
}

bool gtei(const string &n1, const string &n2, int j) {
    for (int i = 0; i <= j; ++i) {
        if (n1[i] > n2[i]) {
            return true;
        } else if (n1[i] < n2[i]) {
            return false;
        }
    }
    return true;
}

bool bounded(const string &n, int i) {
    if (gte(n, nmin))
        return false;
    if (gtei(number, n, i))
        return false;

    return true;
}

void dfs(string n, int i) {
    if (i == imax) {
        if (!valid(n))
            return;

        if (gte(n, number)) {
            if (!gte(n, nmin))
                nmin = n;
        }
        return;
    }

    n[i] = '4';
    if (bounded(n, i))
        dfs(n, i + 1);

    n[i] = '7';
    if (bounded(n, i))
        dfs(n, i + 1);
}

int main() {
    cin >> number;

    if (valid(number)) {
        cout << number;
        return 0;
    }

    int l = number.size();
    if (l % 2 == 0 && gte(string(l, '7'), number))
        imax = l;
    else {
        imax = (number.size() / 2) * 2 + 2;
        string padding = string(imax - l, '0');
        number = padding + number;
    }
    nmin = string(imax / 2, '7') + string(imax / 2, '4');

    string start = string(imax, '4');
    dfs(start, 0);

    cout << nmin;
}

<!-- Iterative Implementation Pending ->