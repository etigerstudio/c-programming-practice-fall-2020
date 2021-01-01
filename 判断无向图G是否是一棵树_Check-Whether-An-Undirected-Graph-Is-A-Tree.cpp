//
// Created by ALuier Bondar on 2020/12/31.
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

vector<vector<int>> connections;
int vcount;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int n1, n2;
        cin >> n1 >> n2;

        int c = max(n1, n2);
        if (c > vcount) {
            vcount = c;
            connections.resize(vcount, vector<int>());
        }
        connections[n1 - 1].push_back(n2 - 1);
        connections[n2 - 1].push_back(n1 - 1);
    }

    bool *visited = new bool[vcount];
    queue<pair<int, int>> q;
    q.push(make_pair(0, -1));
    while (!q.empty()) {
        pair<int, int> t = q.front();
        q.pop();
        int v = get<0>(t);
        int p = get<1>(t);

        if (!visited[v])
            visited[v] = true;
        else {
            cout << "NO";
            return 0;
        }

        for (int i : connections[v]) {
            if (i != p)
                q.push(make_pair(i, v));
        }
    }

    for (int i = 0; i < vcount; ++i) {
        if (!visited[i]){
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";
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

vector<vector<int>> connections;
int vcount;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int n1, n2;
        cin >> n1 >> n2;

        int c = max(n1, n2);
        if (c > vcount) {
            vcount = c;
            connections.resize(vcount, vector<int>());
        }
        connections[n1 - 1].push_back(n2 - 1);
        connections[n2 - 1].push_back(n1 - 1);
    }

    bool *visited = new bool[vcount];
    stack<pair<int, int>> q;
    q.push(make_pair(0, -1));
    while (!q.empty()) {
        pair<int, int> t = q.top();
        q.pop();
        int v = get<0>(t);
        int p = get<1>(t);

        if (!visited[v])
            visited[v] = true;
        else {
            cout << "NO";
            return 0;
        }

        for (int i : connections[v]) {
            if (i != p)
                q.push(make_pair(i, v));
        }
    }

    for (int i = 0; i < vcount; ++i) {
        if (!visited[i]){
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";
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

vector<vector<int>> connections;
bool *visited;

bool visit(int ni, int parent) {
    if (visited[ni])
        return true;

    visited[ni] = true;
    vector<int> l = connections[ni];
    for (int i : l) {
        if (i != parent && visit(i, ni))
            return true;
    }

    return false;
}

int main() {
    int n;
    cin >> n;

    int vcount = 0;
    for (int i = 0; i < n; ++i) {
        int n1, n2;
        cin >> n1 >> n2;

        int c =  max(n1, n2);
        if (c > vcount) {
            connections.resize(c, vector<int>());
            vcount = c;
        }
        connections[n1 - 1].push_back(n2 - 1);
        connections[n2 - 1].push_back(n1 - 1);
    }

    visited = new bool[vcount];
    bool tree = true;
    if (!visit(0, -1)) {
        for (int i = 0; i < vcount; ++i) {
            if (!visited[i]) {
                // Not a connected graph
                tree = false;
                break;
            }
        }
    } else {
        // Looped, not a tree
        tree = false;
    }

    cout << (tree ? "YES" : "NO");
    return 0;
}