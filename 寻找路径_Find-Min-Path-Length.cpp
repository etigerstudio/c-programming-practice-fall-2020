//
// Created by ALuier Bondar on 2021/1/1.
//

<!-- BFS -->

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <list>
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

int main() {
    int n;
    cin >> n;

    auto connections = vector<vector<int>>(n, vector<int>());
    for (int i = 0; i < n - 1; ++i) {
        int n1, n2;
        cin >> n1 >> n2;

        connections[n1 - 1].push_back(n2 - 1);
        connections[n2 - 1].push_back(n1 - 1);
    }

    queue<tuple<int, int, int>> q;
    q.push(make_tuple(0, 0, -1));
    int depth;
    while (!q.empty()) {
        tuple<int, int, int> t = q.front();
        q.pop();
        int v = get<0>(t);
        int d = get<1>(t);
        int p = get<2>(t);
        for (int i : connections[v]) {
            if (i != p)
                q.push(make_tuple(i, d + 1, v));
        }

        if (q.empty())
            depth = d;
    }

    cout << (n - 1) * 2 - depth;
    return 0;
}

<!-- DFS -->

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <list>
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

int main() {
    int n;
    cin >> n;

    auto connections = vector<vector<int>>(n, vector<int>());
    for (int i = 0; i < n - 1; ++i) {
        int n1, n2;
        cin >> n1 >> n2;

        connections[n1 - 1].push_back(n2 - 1);
        connections[n2 - 1].push_back(n1 - 1);
    }

    stack<tuple<int, int, int>> q;
    q.push(make_tuple(0, 0, -1));
    int depth = 0;
    while (!q.empty()) {
        tuple<int, int, int> t = q.top();
        q.pop();
        int v = get<0>(t);
        int d = get<1>(t);
        int p = get<2>(t);
        for (int i : connections[v]) {
            if (i != p)
                q.push(make_tuple(i, d + 1, v));
        }

        depth = max(depth, d);
    }

    cout << (n - 1) * 2 - depth;
    return 0;
}

<!-- DFS (Recursive) -->

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <list>
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

vector<list<int>> connections;
int n;
int maxDepth = numeric_limits<int>::min();

void visit(int ni, int parent, int depth) {
    list<int> l = connections[ni];
    if (l.size() > 1) {
        for (int i : l) {
            if (i != parent) {
                visit(i, ni, depth + 1);
            }
        }
    } else {
        maxDepth = max(maxDepth, depth);
    }
}

int main() {
    cin >> n;

    connections = vector<list<int>>(n, list<int>());
    for (int i = 0; i < n - 1; ++i) {
        int n1, n2;
        cin >> n1 >> n2;

        connections[n1 - 1].push_back(n2 - 1);
        connections[n2 - 1].push_back(n1 - 1);
    }

    visit(0, -1, 0);
    cout << (n - 1) * 2 - maxDepth;
    return 0;
}}