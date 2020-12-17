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
    int n, maxLen = 0;

    cin >> n;
    if (n > 0) {
        string str;
        cin >> str;

        // Beginning of current processing subsequence
        int begin = 0;
        // Mapping from character to last occurence index
        unordered_map<char, int> m;

        for (int i = 0; i < n; i++) {
            auto index = m.find(str[i]);

            // Subsequence is non-duplicating?
            if (index != m.end() && index->second >= begin) {
                // Updating max length
                maxLen = max(maxLen, i - begin);

                // Adjust beginning of current subsequence
                int last = m[str[i]];
                begin = last + 1;
            }

            m[str[i]] = i;
        }

        maxLen = max(maxLen, n - begin);
    }

    cout << maxLen << endl;
    return 0;
}