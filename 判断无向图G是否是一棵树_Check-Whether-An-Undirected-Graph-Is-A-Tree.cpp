//
// Created by ALuier Bondar on 2020/12/31.
//

<!-- Adjacency Matrix -->

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

#define VCOUNT 10000
bool connections[VCOUNT][VCOUNT], visited[VCOUNT];
bool looped = false;
int n;

bool visit(int ni, int parent) {
    if (visited[ni])
        return true;

    visited[ni] = true;
    for (int i = 0; i < n; ++i) {
        if (i != ni && i != parent && connections[ni][i]) {
            if (visit(i, ni)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int n1, n2;
        cin >> n1 >> n2;

        connections[n1 - 1][n2 - 1] = true;
        connections[n2 - 1][n1 - 1] = true;
    }

    looped = visit(0, -1);
    bool tree = !looped;
    if (tree)
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                tree = false;
                break;
            }
        }

    cout << (tree ? "YES" : "NO");
    return 0;
}

<!-- Adjacency List -->

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

unordered_map<int, list<int>> connections;
bool *visited;
bool looped = false;
int vcount;

bool visit(int ni, int parent) {
    if (visited[ni])
        return true;

    visited[ni] = true;
    list<int> l = connections[ni];
    for (int i = 0; i < vcount; ++i) {
        if (i != ni && i != parent && find(l.begin(), l.end(), i) != l.end()) {
            if (visit(i, ni)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int n1, n2;
        cin >> n1 >> n2;

        vcount = max(vcount, max(n1, n2));
        connections[n1 - 1].push_back(n2 - 1);
        connections[n2 - 1].push_back(n1 - 1);
    }

    visited = new bool[vcount];
    looped = visit(0, -1);
    bool tree = !looped;
    if (tree)
        for (int i = 0; i < vcount; ++i) {
            if (!visited[i]) {
                tree = false;
                break;
            }
        }

    cout << (tree ? "YES" : "NO");
    return 0;
}