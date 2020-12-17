//
// Created by ALuier Bondar on 2020/11/6.
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

using namespace std;

typedef struct Node {
    Node *left, *right;
    int val;
    explicit Node(int val) : val(val), left(nullptr), right(nullptr) {};
} Node, *Tree;

void visitNode(Node* n) {
    if (n == nullptr) return;
    cout << n->val << ' ';
}

void postTraverse(Tree t) {
    if (t == nullptr) return;

    postTraverse(t->left);
    postTraverse(t->right);
    visitNode(t);
}

Tree generateTree(const int *pre, const int *in, int n) {
    if (n == 1) return new Node(pre[0]);

    int root = pre[0];
    int split;
    for (int i = 0; i < n; ++i) {
        if (in[i] == root) {
            split = i;
            break;
        }
    }

    Tree t = new Node(root);
    int lhs = split;
    int rhs = n - lhs - 1;
    if (lhs > 0)
        t->left = generateTree(pre + 1, in, lhs);
    if (rhs > 0)
        t->right = generateTree(pre + lhs + 1, in + lhs + 1, rhs);
    return t;
}

int main() {
    int n;
    cin >> n;

    int *pre = new int[n], *in = new int[n];

    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        pre[i] = val;
    }
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        in[i] = val;
    }

    Tree t = generateTree(pre, in, n);
    postTraverse(t);

    return 0;
}
