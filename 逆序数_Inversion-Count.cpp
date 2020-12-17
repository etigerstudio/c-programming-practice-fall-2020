//
// Created by ALuier Bondar on 2020/12/17.
//

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

using namespace std;

int main() {
    int n, ans;
    cin >> n;

    long *nums = new long[n];
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        nums[i] = abs(nums[i]);
    }
    for (int i = 0; i < n; ++i) {
        int l = 0, r = 0;
        for (int j = 0; j < i; ++j) if(nums[j] < nums[i]) ++l;
        for (int j = i + 1; j < n; ++j) if(nums[j] < nums[i]) ++r;
        ans += min(l, r);
    }
    cout << ans;
    return 0;
}