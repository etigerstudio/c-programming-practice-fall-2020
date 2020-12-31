//
// Created by ALuier Bondar on 2020/12/29.
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

typedef struct Node {
    Node *left;
    Node *right;
    int val;

    Node() : left(nullptr), right(nullptr), val(0) {};
    Node(int val) : left(nullptr), right(nullptr), val(val) {};
} Node, *Tree;

int maxSum = numeric_limits<int>::min();

int calcPathGain(Tree root)
{
    if (root == nullptr) return 0;

    int left = calcPathGain(root->left);
    int right = calcPathGain(root->right);

    int sum = root->val + max(0, left) + max(0, right);
    maxSum = max(maxSum, sum);

    int gain = root->val + max(0, max(left, right));
    return gain;
}

int main() {
    int n;
    cin >> n;

    if (n == 0) {
        cout << 0;
        return 0;
    }

    Node *nodes;
    nodes = new Node[n];
    for (int i = 0; i < n; ++i) {
        int left, right, val;
        cin >> left >> right >> val;

        if (left > 0)
            nodes[i].left = &nodes[left - 1];
        if (right > 0)
            nodes[i].right = &nodes[right - 1];
        nodes[i].val = val;
    }

    calcPathGain(&nodes[0]);
    cout << maxSum;
    return 0;
}