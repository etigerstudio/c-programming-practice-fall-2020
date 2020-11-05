//
// Created by ALuier Bondar on 2020/11/3.
//

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <limits>
#include <iomanip>

using namespace std;

typedef struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {};
    Point() : x(0), y(0) {};
} Point;

float calcDist(Point p1, Point p2) {
    return sqrt(pow(float(p1.x - p2.x), 2.f) +
                pow(float(p1.y - p2.y), 2.f));
}

float bruteMinDist(Point s[], int n) {
    float minDist = numeric_limits<float>::max();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            minDist = min(calcDist(s[i], s[j]), minDist);
        }
    }

    return minDist;
}

int comparePY(const void* p1, const void* p2) {
    return ((Point*) p1)->y - ((Point*) p2)->y;
}

float stripMinDist(Point s[], int n, float d) {
    float dmin = d;

    // TODO: Pre-sort by Y
    qsort(s, n, sizeof(Point), comparePY);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n && s[j].y - s[i].y < dmin; j++) {
            dmin = min(calcDist(s[i], s[j]), dmin);
        }
    }

    return dmin;
}

int comparePX(const void* p1, const void* p2) {
    return ((Point*) p1)->x - ((Point*) p2)->x;
}

float findMinDist(Point s[], int n) {
    if (n <= 3) return bruteMinDist(s, n);

    int mid = n / 2;
    float dl = findMinDist(s, mid);
    float dr = findMinDist(s + mid, n - mid);
    float dmin = min(dl, dr);

    vector<Point> strip;
    Point midPoint = s[mid];
    for (int i = 0; i < n; i++) {
        if (abs(s[i].x - midPoint.x) < dmin) {
            strip.push_back(s[i]);
        }
    }

    float dstrip = stripMinDist(strip.data(), strip.size(), dmin);
    return min(dmin, dstrip);
}

int main() {
    int n;
    cin >> n;

    Point *p = new Point[n];
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    qsort(p, n, sizeof(Point), comparePX);

    cout << fixed << setprecision(4);
    float dmin = findMinDist(p, n);
    if (dmin < 10000) {
        cout << dmin << endl;
    } else {
        cout << "INFINITY" << endl;
    }

    return 0;
}
