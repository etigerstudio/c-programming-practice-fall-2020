//
// Created by ALuier Bondar on 2020/12/11.
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
    int n, k;
    cin >> n >> k;

    int *nums = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    sort(nums, nums + n);

    int additions = 0, reductions = 0;
    for (int i = 0; i < k; ++i) {
        additions += nums[k - 1] - nums[i];
        reductions += nums[n - i - 1] - nums[n - k];
    }

    int i1 = k, i2 = n - k - 1;
    while (i1 < n && nums[i1++] == nums[k - 1]) additions--;
    while (i2 >= n && nums[i2--] == nums[n - k]) reductions--;
    cout << max(0, min(additions, reductions));
    return 0;
}