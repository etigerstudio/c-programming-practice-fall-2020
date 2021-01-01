//
// Created by ALuier Bondar on 2021/1/1.
//

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

#define VCOUNT 100

int main() {
    int n, m, begin, end;
    cin >> n >> m >> begin >> end;
    --begin, --end;

    bool connections[VCOUNT][VCOUNT]{false};
    for (int i = 0; i < m; ++i) {
        int n1, n2;
        cin >> n1 >> n2;

        connections[n1 - 1][n2 - 1] = true;
    }

    bool visited[VCOUNT]{false};
    stack<pair<int, int>> q;
    q.push(make_pair(begin, -1));
    while (!q.empty()) {
        pair<int, int> t = q.top();
        q.pop();
        int v = get<0>(t);
        int p = get<1>(t);

        if (!visited[v])
            visited[v] = true;
        else
            continue;

        if (v == end) {
            cout << 1;
            return 0;
        }

        for (int i = 0; i < n; ++i) {
            if (i != p && connections[v][i])
                q.push(make_pair(i, v));
        }
    }

    cout << 0;
    return 0;
}

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

#define VCOUNT 100

int main() {
    int n, m, begin, end;
    cin >> n >> m >> begin >> end;
    --begin, --end;

    bool connections[VCOUNT][VCOUNT]{false};
    for (int i = 0; i < m; ++i) {
        int n1, n2;
        cin >> n1 >> n2;

        connections[n1 - 1][n2 - 1] = true;
    }

    bool visited[VCOUNT]{false};
    queue<pair<int, int>> q;
    q.push(make_pair(begin, -1));
    while (!q.empty()) {
        pair<int, int> t = q.front();
        q.pop();
        int v = get<0>(t);
        int p = get<1>(t);

        if (!visited[v])
            visited[v] = true;
        else
            continue;

        if (v == end) {
            cout << 1;
            return 0;
        }

        for (int i = 0; i < n; ++i) {
            if (i != p && connections[v][i])
                q.push(make_pair(i, v));
        }
    }

    cout << 0;
    return 0;
}