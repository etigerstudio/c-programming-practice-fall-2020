//
// Created by ALuier Bondar on 2020/12/22.
//

<!-- O(n^2) iteration -->

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

#define BOX '#'
#define UNUSED 0
#define OCCUPIED 1
#define VALID 1
#define INVALID 0

using namespace std;

int n, m, **boxes, c;
set<string> ans;

int isValid(int i, int j) {
    for (int k = 0; k < c; ++k) {
        if (boxes[k][2] == OCCUPIED) {
            if (boxes[k][0] == i || boxes[k][1] == j)
                return INVALID;
        }
    }

    return VALID;
}

void insertAns() {
    string s = string(c, '0');
    for (int i = 0; i < c; ++i) {
        if (boxes[i][2] == OCCUPIED)
            s[i] = '1';
    }
    ans.insert(s);
}

void dfs(int d) {
    if (d == m) {
        insertAns();
        return;
    }

    for (int i = 0; i < c; ++i) {
        if (boxes[i][2] == UNUSED && isValid(boxes[i][0], boxes[i][1])) {
            boxes[i][2] = OCCUPIED;
            dfs(d + 1);
            boxes[i][2] = UNUSED;
        }
    }
}

int main() {
    cin >> n >> m;

    c = 0;
    boxes = new int *[n * n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char tmp;
            cin >> tmp;
            if (tmp == BOX) {
                boxes[c] = new int[3]{i, j, UNUSED};
                ++c;
            }
        }
    }

    dfs(0);

    cout << ans.size();
    return 0;
}

<!-- O(n) aux array + efficient dfs -->

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

#define BOX '#'
#define UNUSED 0
#define OCCUPIED 1

using namespace std;

int n, m, **boxes, c;
int *cols, *rows;
set<string> ans;

void insertAns() {
    string s = string(c, '0');
    for (int i = 0; i < c; ++i) {
        if (boxes[i][2] == OCCUPIED)
            s[i] = '1';
    }
    ans.insert(s);
}

void dfs(int d, int i) {
    if (d == m) {
        insertAns();
        return;
    }
    if (i == c) {
        return;
    }

    if (rows[boxes[i][0]] == 0 && cols[boxes[i][1]] == 0) {
        ++rows[boxes[i][0]];
        ++cols[boxes[i][1]];
        boxes[i][2] = OCCUPIED;
        dfs(d + 1, i + 1);
        --rows[boxes[i][0]];
        --cols[boxes[i][1]];
        boxes[i][2] = UNUSED;
    }
    dfs(d, i + 1);
}

int main() {
    cin >> n >> m;

    c = 0;
    boxes = new int *[n * n];
    cols = new int[n]{0};
    rows = new int[n]{0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char tmp;
            cin >> tmp;
            if (tmp == BOX) {
                boxes[c] = new int[3]{i, j, UNUSED};
                ++c;
            }
        }
    }

    dfs(0, 0);

    cout << ans.size();
    return 0;
}