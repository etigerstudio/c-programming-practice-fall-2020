//
// Created by ALuier Bondar on 2020/9/27.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    int n;
    cin >> n;

    int dup;
    // Light-weight map implemented by an array
    bool* m = new bool[n];
    for (int i = 0; i < n + 1; i++) {
        int num;
        cin >> num;

        // Current number has already existed?
        if (m[num - 1]) {
            // Duplication found!
            dup = num;
            break;
        } else {
            // Storing current number
            m[num - 1] = true;
        }
    }

    delete [] m;

    cout << dup << endl;
    return 0;
}
