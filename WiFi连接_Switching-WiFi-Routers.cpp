//
// Created by ALuier Bondar on 2020/11/5.
//

<!-- W. wifi pre-sorting(iterations halved) -->

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <limits>
#include <iomanip>
#include <cmath>

using namespace std;

typedef struct Point {
    float x, y, d;
    Point(float x, float y) : x(x), y(y), d(-1) {};
    Point() : x(0), y(0), d(-1) {};
} Point;

typedef struct Vector {
    float i, j;
    Vector(float i, float j) : i(i), j(j) {};
    Vector() : i(0), j(0) {};
} Vector;

int n, m, k;
Point *tests, *wifis;

float distanceBetween(Point start, Point end, Point p) {
    return abs((end.y - start.y) * p.x -
               (end.x - start.x) * p.y +
               end.x * start.y - end.y * start.x) /
           sqrt(pow(end.y - start.y, 2.f) +
                pow(end.x - start.x, 2.f));
}

float distanceBetween(Point p1, Point p2) {
    return sqrt(pow(p1.y - p2.y, 2.f) +
                pow(p1.x - p2.x, 2.f));
}

// Calc projection length of v1 on v2
float projectionUpon(Vector v1, Vector v2) {
    float dot = v1.i * v2.i + v1.j * v2.j;
    float len2 = sqrt(pow(v2.i, 2.f) + pow(v2.j, 2.f));
    return dot / len2;
}

float normalDistance(Point start, Point end, Point p) {
    Vector v1 = Vector(p.x - start.x, p.y - start.y);
    Vector v2 = Vector(end.x - start.x, end.y - start.y);
    return projectionUpon(v1, v2);
}

float yByX(float x, Point start, Point end) {
    float dy = end.y - start.y, dx = end.x - start.x;
    if (dx == 0) {
        return -1; // s = inf, Vertical
    } else {
        return start.y + (x - start.x) * (dy / dx);
    }
}

float xByY(float y, Point start, Point end) {
    float dy = end.y - start.y, dx = end.x - start.x;
    if (dy == 0) {
        return -1; // s = 0, Horizontal
    } else {
        return start.x + (y - start.y) * (dx / dy);
    }
}

// Is v in between v1 & v2?
bool inRange(float v1, float v2, float v) {
    if (v1 > v2) {
        return v > v2 && v < v1;
    } else {
        return v > v1 && v < v2;
    }
}

float distanceWhenMeet(Point start, Point end, Point p1, Point p2) {
    Point mid = Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);

    float dy = p2.y - p1.y, dx = p2.x - p1.x;
    Point p;
    if (dy == 0) { // Horizontal
        if (inRange(start.x, end.x, mid.x)) {
            p = Point(mid.x, yByX(mid.x, start, end));
        } else {
            return -1;
        }
    } else if (dx == 0) { // Vertical
        if (inRange(start.y, end.y, mid.y)) {
            p = Point(xByY(mid.y, start, end), mid.y);
        } else {
            return -1;
        }
    } else {
        float dy2 = end.y - start.y, dx2 = end.x - start.x;
        if (dy2 == 0) { // Horizontal
            float x = xByY(start.y, p1, p2);
            if (inRange(start.x, end.x, x)) {
                p = Point(x, start.y);
            } else {
                return -1;
            }
        } else if (dx2 == 0) { // Vertical
            float y = yByX(start.x, p1, p2);
            if (inRange(start.y, end.y, y)) {
                p = Point(start.x, y);
            } else {
                return -1;
            }
        } else {
            float k1 = - dx / dy, k2 = dy2 / dx2;
            if (k1 == k2) return -1; // Not intersecting at all
            float x = (k1 * mid.x - mid.y - k2 * end.x + end.y) / (k1 - k2);
            float y = k2 * (x - end.x) + end.y;
            if (inRange(start.x, end.x, x) && inRange(start.y, end.y, y)) {
                p = Point(x, y);
            } else {
                return -1;
            }
        }
    }

    return distanceBetween(start, p);
}

int compareNormalDist(const void* p1, const void* p2) {
    // Ignoring overflow for it's not likely to happen
    float d1 = ((Point*) p1)->d;
    float d2 = ((Point*) p2)->d;
    if (d1 > d2) return 1;
    if (d1 < d2) return -1;
    return 0;
}

int totalSwitches(Point start, Point end) {
    int switches = 0, wifi = 0;

    // Sort wifis along testing line
    Point w[m]; // A copy of all wifi points to be sorted
    for (int i = 0; i < m; i++) {
        w[i] = wifis[i];
        w[i].d = normalDistance(start, end, w[i]);
    }
    qsort(w, m, sizeof(Point), compareNormalDist);

    // Determine initial wifi index
    float dmin = numeric_limits<float>::max();
    for (int i = 0; i < m; i++) {
        float d = distanceBetween(start, w[i]);
        if (d < dmin) {
            dmin = d;
            wifi = i;
        }
    }

    // Determine next wifi index
    float cm = 0; // Current meeting point
    bool switched;
    do {
        switched = false;
        float mmin = numeric_limits<float>::max();
        int imin = 0;
        for (int i = wifi + 1; i < m; i++) {
            float meet = distanceWhenMeet(start, end, w[wifi], w[i]);
            if (meet > cm && meet < mmin) {
                switched = true;
                mmin = meet;
                imin = i;
            }
        }

        if (switched) {
            ++switches;
            cm = mmin;
            wifi = imin;
        }
    } while (switched);

    return switches;
}

int main() {
    cin >> n >> m;
    // Testing Locations, Wifi Locations
    tests = new Point[n];
    wifis = new Point[m];
    for (int i = 0; i < n; i++) {
        cin >> tests[i].x >> tests[i].y;
    }
    for (int i = 0; i < m; i++) {
        cin >> wifis[i].x >> wifis[i].y;
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        int start, end;
        cin >> start >> end;
        cout << totalSwitches(tests[start - 1], tests[end - 1]) << endl;
    }

    return 0;
}


<!-- W/O wifi pre-sorting -->

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <limits>
#include <iomanip>
#include <cmath>

using namespace std;

typedef struct Point {
    float x, y;
    Point(float x, float y) : x(x), y(y) {};
    Point() : x(0), y(0) {};
} Point;

int n, m, k;
Point *tests, *wifis;

float distanceBetween(Point start, Point end, Point p) {
    return abs((end.y - start.y) * p.x -
               (end.x - start.x) * p.y +
               end.x * start.y - end.y * start.x) /
           sqrt(pow(end.y - start.y, 2.f) +
                pow(end.x - start.x, 2.f));
}

float distanceBetween(Point p1, Point p2) {
    return sqrt(pow(p1.y - p2.y, 2.f) +
                pow(p1.x - p2.x, 2.f));
}

float yByX(float x, Point start, Point end) {
    float dy = end.y - start.y, dx = end.x - start.x;
    if (dx == 0) {
        return -1; // s = inf, Vertical
    } else {
        return start.y + (x - start.x) * (dy / dx);
    }
}

float xByY(float y, Point start, Point end) {
    float dy = end.y - start.y, dx = end.x - start.x;
    if (dy == 0) {
        return -1; // s = 0, Horizontal
    } else {
        return start.x + (y - start.y) * (dx / dy);
    }
}

// Is v in between v1 & v2?
bool inRange(float v1, float v2, float v) {
    if (v1 > v2) {
        return v > v2 && v < v1;
    } else {
        return v > v1 && v < v2;
    }
}

float distanceWhenMeet(Point start, Point end, Point p1, Point p2) {
    Point mid = Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);

    float dy = p2.y - p1.y, dx = p2.x - p1.x;
    Point p;
    if (dy == 0) { // Horizontal
        if (inRange(start.x, end.x, mid.x)) {
            p = Point(mid.x, yByX(mid.x, start, end));
        } else {
            return -1;
        }
    } else if (dx == 0) { // Vertical
        if (inRange(start.y, end.y, mid.y)) {
            p = Point(xByY(mid.y, start, end), mid.y);
        } else {
            return -1;
        }
    } else {
        float dy2 = end.y - start.y, dx2 = end.x - start.x;
        if (dy2 == 0) { // Horizontal
            float x = xByY(start.y, p1, p2);
            if (inRange(start.x, end.x, x)) {
                p = Point(x, start.y);
            } else {
                return -1;
            }
        } else if (dx2 == 0) { // Vertical
            float y = yByX(start.x, p1, p2);
            if (inRange(start.y, end.y, y)) {
                p = Point(start.x, y);
            } else {
                return -1;
            }
        } else {
            float k1 = - dx / dy, k2 = dy2 / dx2;
            if (k1 == k2) return -1; // Not intersecting at all
            float x = (k1 * mid.x - mid.y - k2 * end.x + end.y) / (k1 - k2);
            float y = k2 * (x - end.x) + end.y;
            if (inRange(start.x, end.x, x) && inRange(start.y, end.y, y)) {
                p = Point(x, y);
            } else {
                return -1;
            }
        }
    }

    return distanceBetween(start, p);
}

int totalSwitches(Point start, Point end) {
    int switches = 0, wifi = 0;

    // TODO: Pre-sort wifis to reduce complexity

    // Determine initial wifi index
    float dmin = numeric_limits<float>::max();
    for (int i = 0; i < m; i++) {
        float d = distanceBetween(start, wifis[i]);
        if (d < dmin) {
            dmin = d;
            wifi = i;
        }
    }

    // Determine next wifi index
    float cm = 0; // Current meeting point
    bool switched;
    do {
        switched = false;
        float mmin = numeric_limits<float>::max();
        int imin = 0;
        for (int i = 0; i < m; i++) {
            if (i == wifi) continue;

            float meet = distanceWhenMeet(start, end, wifis[wifi], wifis[i]);
            if (meet > cm && meet < mmin) {
                switched = true;
                mmin = meet;
                imin = i;
            }
        }

        if (switched) {
            ++switches;
            cm = mmin;
            wifi = imin;
        }
    } while (switched);

    return switches;
}

int main() {
    cin >> n >> m;
    // Testing Locations, Wifi Locations
    tests = new Point[n];
    wifis = new Point[m];
    for (int i = 0; i < n; i++) {
        cin >> tests[i].x >> tests[i].y;
    }
    for (int i = 0; i < m; i++) {
        cin >> wifis[i].x >> wifis[i].y;
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        int start, end;
        cin >> start >> end;
        cout << totalSwitches(tests[start - 1], tests[end - 1]) << endl;
    }

    return 0;
}