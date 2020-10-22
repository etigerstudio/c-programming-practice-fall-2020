//
// Created by ALuier Bondar on 2020/10/15.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>

using namespace std;

typedef struct Node {
    int data;
    Node* next;
} Node, *List;

void printList(List list) {
    Node* cur = list;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    k %= n;

    List list = new Node;
    list->next = nullptr;
    Node* cur = list;
    Node* before = nullptr;
    Node* after = nullptr;
    for (int i = 0; i < n; i++) {
        Node *node = new Node;
        node->next = nullptr;
        cin >> node->data;
        cur->next = node;
        cur = node;

        if (i == n - k) before = node;
        if (i == n - k + 1) after = node;
    }
    Node* begin = list->next;
    Node* end = cur;

    list->next = after;
    end->next = begin;
    before->next = nullptr;

    printList(list->next);
    return 0;
}
