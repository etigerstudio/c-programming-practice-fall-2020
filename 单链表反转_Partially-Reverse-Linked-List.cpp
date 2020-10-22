//
// Created by ALuier Bondar on 2020/10/9.
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
    int n, a, b;
    cin >> n >> a >> b;

    List list = (List) malloc(sizeof(Node));
    list->next = nullptr;
    Node* cur = list;
    for (int i = 0; i < n; i++) {
        Node *node = (Node *) malloc(sizeof(Node));
        node->next = nullptr;
        cin >> node->data;
        cur->next = node;
        cur = node;
    }

    if (a != b) {
        Node *pre, *begin, *end, *post;
        int preloc = a - 2;
        int beginloc = a - 1;
        int endloc = b - 1;
        int postloc = b;

        cur = list->next;
        for (int i = 0; i < n; i++) {
            if (i == preloc) pre = cur;
            if (i == beginloc) begin = cur;
            if (i == endloc) end = cur;
            if (i == postloc) post = cur;

            cur = cur->next;
        }

        Node* n1 = begin;
        Node* n2 = begin->next;
        for (int i = 0; i < b - a; i++) {
            Node* tmp = n2->next;
            n2->next = n1;
            n1 = n2;
            n2 = tmp;
        }

        if (preloc >= 0) {
            pre->next = end;
        } else {
            list->next = end;
        }
        if (postloc < n) {
            begin->next = post;
        } else {
            begin->next = nullptr;
        }
    }

    printList(list->next);
    return 0;
}
