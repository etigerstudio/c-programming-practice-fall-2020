//
// Created by ALuier Bondar on 2020/10/22.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>

using namespace std;

typedef struct Node {
    int val;
    Node *next;
} Node, *List;

void printList(List list, int maxLen) {
    int len = 0;
    Node *cur = list;
    while (cur != nullptr && len < maxLen) {
        cout << cur->val << " ";
        cur = cur->next;
        len++;
    }
}

List seekList(List list, int stride) {
    List cur = list;
    while (stride > 0) {
        cur = cur->next;
        stride--;
    }

    return cur;
}

List mergeList(List l1, int n1, List l2, int n2) {
    if (n1 == 0 && n2 == 0) {
        return nullptr;
    } else if (n1 == 0 && n2 > 0) {
        return l2;
    } else if (n1 > 0 && n2 == 0) {
        return l1;
    } else {
        List list = new Node; // Dummy head
        Node *cur = list;
        while (n1 > 0 && n2 > 0) {
            if (l1->val < l2->val) {
                cur->next = l1;
                cur = l1;
                l1 = l1->next;
                n1--;
            } else {
                cur->next = l2;
                cur = l2;
                l2 = l2->next;
                n2--;
            }
        }
        while (n1 > 0) {
            cur->next = l1;
            cur = l1;
            l1 = l1->next;
            n1--;
        }
        while (n2 > 0) {
            cur->next = l2;
            cur = l2;
            l2 = l2->next;
            n2--;
        }

        return list->next;
    }
}

List mergeSort(List list, int n) {
    if (n <= 1) return list; // Baseline

    int n1 = n / 2 + n % 2;
    int n2 = n / 2;

    List left = list;
    List right = seekList(list, n1);

    return mergeList( // Merge
            mergeSort(left, n1), n1, // Sort left hand side
            mergeSort(right, n2), n2 // Sort right hand side
    );
}

int main() {
    int n;
    cin >> n;

    List list = new Node;
    list->next = nullptr;
    Node *cur = list;
    for (int i = 0; i < n; i++) {
        Node *node = new Node;
        node->next = nullptr;
        cin >> node->val;
        cur->next = node;
        cur = node;
    }

    printList(mergeSort(list->next, n), n);
    return 0;
}
