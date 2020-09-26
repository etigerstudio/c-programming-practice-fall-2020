//
// Created by ALuier Bondar on 2020/9/27.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    int n;
    cin >> n;

    while (n != 0) {
        vector<int> dp = vector<int>(n);

        int tmp;
        cin >> tmp;
        dp[0] = tmp;

        for (int i = 1; i < n; i++) {
            cin >> tmp;
            dp[i] = max(tmp, dp[i - 1] + tmp);
        }
        cout << *max_element(dp.begin(), dp.end()) << endl;

        cin >> n;
    }

    return 0;
}