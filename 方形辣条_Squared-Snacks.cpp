//
// Created by ALuier Bondar on 2020/12/19.
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
#include <cstdlib>

using namespace std;

int n, *nums, bound;

static bool gt(int &a,int &b){
    return a > b;
}

void dfs(int d, int *l) {
    if (d == n - 1) {
        cout << "yes";
        exit(0);
    }

    int cur = nums[d + 1];
    for (int i = 0; i <= 3; ++i) {
        if (l[i] + cur <= bound) {
            l[i] += cur;
            dfs(d + 1, l);
            l[i] -= cur;
        }
    }
}

int main() {
    cin >> n;

    nums = new int[n];
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        sum += nums[i];
    }

    if (sum % 4 != 0) {
        cout << "no";
        return 0;
    }

    bound = sum / 4;
    for (int i = 0; i < n; ++i) {
        if (nums[i] > bound) {
            cout << "no";
            return 0;
        }
    }

    sort(nums, nums + n, gt);
    int *l = new int[4]{0};
    l[0] = nums[0];
    dfs(0, l);

    cout << "no";
    return 0;
}