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

void bfs(Tree t) {
    queue<Node*> s;
    s.push(t);

    while (!s.empty()) {
        Node* n = s.front();
        s.pop();

        visitNode(n);
        if (n->left) s.push(n->left);
        if (n->right) s.push(n->right);
    }
}

void preTraverseI1(Tree t) {
    stack<Node*> s;
    s.push(t);

    while (!s.empty()) {
        Node* n = s.top();
        s.pop();

        visitNode(n);
        if (n->right) s.push(n->right);
        if (n->left) s.push(n->left);
    }
}

void preTraverseI2(Tree t) {
    stack<Node*> s;

    Node* cur = t;
    while (cur || !s.empty()) {
        while (cur) {
            visitNode(cur);

            if (cur->right) s.push(cur->right);
            cur = cur->left;
        }

        if (!s.empty()) {
            cur = s.top();
            s.pop();
        }
    }
}

void inTraverseI(Tree t) {
    stack<Node*> s;

    Node* cur = t;
    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }

        if (!s.empty()) {
            cur = s.top();
            s.pop();

            visitNode(cur);
            cur = cur->right;
        }
    }
}

void postTraverseI1(Tree t) {
    stack<Node*> s1, s2;
    s1.push(t);

    while (!s1.empty()) {
        Node *n = s1.top();
        s1.pop();

        s2.push(n);
        if(n->left) s1.push(n->left);
        if(n->right) s1.push(n->right);
    }

    while (!s2.empty()) {
        visitNode(s2.top());
        s2.pop();
    }
}

void postTraverseI2(Tree t) {
    stack<Node*> s;
    Node* cur = t;

    while (cur || !s.empty()) {
        while (cur) {
            if (cur->right) s.push(cur->right);
            s.push(cur);
            cur = cur->left;
        }

        if (!s.empty()) {
            cur = s.top();
            s.pop();

            if (cur->right && !s.empty() && s.top() == cur->right) {
                s.pop();
                s.push(cur);
                cur = cur->right;
            } else {
                visitNode(cur);
                cur = nullptr;
            }
        }
    }
}

void preTraverseR(Tree t) {
    if (!t) return;

    visitNode(t);
    preTraverseR(t->left);
    preTraverseR(t->right);
}

void inTraverseR(Tree t) {
    if (!t) return;

    inTraverseR(t->left);
    visitNode(t);
    inTraverseR(t->right);
}

void postTraverseR(Tree t) {
    if (!t) return;

    postTraverseR(t->left);
    postTraverseR(t->right);
    visitNode(t);
}

int main() {
    int n;
    cin >> n;

    Tree t = new Node(1);

    Node **nodes = new Node*[n];
    nodes[0] = t;
    for (int i = 0; i < n; i++) {
        int lval, rval;
        cin >> lval >> rval;

        if (lval) {
            Node *ln = new Node(lval);
            nodes[lval - 1] = ln;
            nodes[i]->left = ln;
        }

        if (rval) {
            Node *rn = new Node(rval);
            nodes[rval - 1] = rn;
            nodes[i]->right = rn;
        }
    }

    bfs(t);
    cout << endl;
    preTraverseI1(t);
    cout << endl;
    preTraverseI2(t);
    cout << endl;
    preTraverseR(t);
    cout << endl;
    inTraverseI(t);
    cout << endl;
    inTraverseR(t);
    cout << endl;
    postTraverseI1(t);
    cout << endl;
    postTraverseI2(t);
    cout << endl;
    postTraverseR(t);

    return 0;
}
