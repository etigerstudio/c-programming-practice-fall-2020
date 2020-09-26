//
// Created by ALuier Bondar on 2020/9/27.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

int n;
string str;
int maxLen = 0;

void spread(int l, int r) {
    int iter = max(l, n - r - 1);
    for (int j = 0; j < iter; j++) {
        if (str[l - 1] != str[r + 1]) break;
        l--; r++;
    }
    maxLen = max(maxLen, r - l + 1);
}

int main() {
    cin >> n;

    if (n > 0) {
        cin >> str;
        maxLen = 1;
        for (int i = 0; i + 1 < n; i++) {
            int l, r;
            if (str[i] == str[i + 1]) {
                spread(i, i + 1);
            }
            if (i - 1 >= 0 && str[i - 1] == str[i + 1]) {
                spread(i - 1, i + 1);
            }
        }
    }

    cout << maxLen << endl;
    return 0;
}