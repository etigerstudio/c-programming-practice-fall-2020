//
// Created by ALuier Bondar on 2020/9/27.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

int rows, columns;
int maxN;
vector<bool> visited;
vector<bool> vals;
int n = 0;

void detect(int idx);
void visit(int idx);
void visitIfExists(int x, int y);

int main() {
    cin >> rows >> columns;
    maxN = rows * columns;
    visited = vector<bool>(maxN);

    char tmp;
    vals = vector<bool>(rows * columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin >> tmp;
            if (tmp == '.') {
                vals[i * columns + j] = false;
            } else {
                vals[i * columns + j] = true;
            }
        }
    }

    for (int i = 0; i < maxN; i++)
        detect(i);

    cout << n;

    return 0;
}

void detect(int idx) {
    if (visited[idx])
        return;

    if (vals[idx]) {
        n++;
        visit(idx);
    }
}

void visit(int idx) {
    if (visited[idx]) {
        // Early exit
        return;
    } else {
        // Marking visited
        visited[idx] = true;
    }

    // Indices to Pos
    int x, y;
    x = idx % columns;
    y = idx / columns;

    // Visit surroundings by Recursing
    visitIfExists(x - 1, y - 1);
    visitIfExists(x, y - 1);
    visitIfExists(x + 1, y - 1);
    visitIfExists(x - 1, y);
    visitIfExists(x + 1, y);
    visitIfExists(x - 1, y + 1);
    visitIfExists(x, y + 1);
    visitIfExists(x + 1, y + 1);
}

void visitIfExists(int x, int y) {
    // Pos in Bounding Box?
    if (x >= 0 && x < columns && y >= 0 && y < rows) {
        // Pos to Indices
        int idx = y * columns + x;
        if (vals[idx]) {
            // Perform Visiting
            visit(idx);
        }
    }
}