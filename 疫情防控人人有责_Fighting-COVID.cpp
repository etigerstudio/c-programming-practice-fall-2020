//
// Created by ALuier Bondar on 2020/9/27.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

// To be implemented with Union-Find Set to improve performance

int main() {
    int stu, apart;
    cin >> stu >> apart;

    while (stu > 0 || apart > 0) {
        map<int, set<int>> a2s;
        map<int, set<int>> s2a;

        for (int i = 0; i < apart; i++) {
            int n, tmp;
            cin >> n;
            auto a = set<int>();
            for (int j = 0; j < n; j++) {
                cin >> tmp;
                a.insert(tmp);

                s2a[tmp].insert(i);
            }
            a2s[i] = a;
        }

        auto infected = set<int>();
        infected.insert(0);
        for (int a1: s2a[0]) {
            for (int s1: a2s[a1]) {
                for (int a2: s2a[s1]) {
                    for (int s2: a2s[a2]) {
                        infected.insert(s2);
                    }
                }
            }
        }
        cout << infected.size() << endl;

        cin >> stu >> apart;
    }

    return 0;
}