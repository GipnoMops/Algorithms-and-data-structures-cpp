#include <iostream>
#include <vector>
const int EPS = 1E-9;

struct Point {
    int x, y;
};

int sgn (int x) {
    if (x >= 0.0) return 1;
    else return -1;
}

bool point_on_line (int x0, int y0, int x1, int y1, int x2, int y2) {

    if ((x0 == x1 && y0 == y1) || (x0 == x2 && y0 == y2)) return true;
    if (x0 * (y2 - y1) + y0 * (x1 - x2) + (y1 * x2 - x1 * y2) <= EPS) {
        if ((y2 - y1 >= EPS && y0 - y1 >= EPS && y0 - y2 <= EPS) ||
            (y2 - y1 <= EPS && y0 - y1 <= EPS && y0 - y2 >= EPS)) {
            if (y1 == y0 == y2) {
                if ((x2 >= x1 && x0 >= x1 && x0 <= x2) || (x2 <= x1 && x0 <= x1 && x0 >= x2)) return true;
                else return false;
            } else return true;
        } else return false;
    } else return false;

}



bool intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    int a1, b1, c1, a2, b2, c2;
    a1 = y2 - y1; b1 = x1 - x2; c1 = y1 * x2 - x1 * y2;
    a2 = y4 - y3; b2 = x3 - x4; c2 = y3 * x4 - x3 * y4;

    int flag;
    int b3, c3;
    if (a1 * b2 == b1 * a2) {
        if (a1 * c2 == c1 * a2) flag = 2;
        else flag = 0;
    } else flag = 1;

    if (flag == 1) {
        if (sgn((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) !=
            sgn((x2 - x1) * (y4 - y1) - (x4 - x1) * (y2 - y1)) &&
            sgn((x4 - x3) * (y1 - y3) - (x1 - x3) * (y4 - y3)) !=
            sgn((x4 - x3) * (y2 - y3) - (x2 - x3) * (y4 - y3))) return true;
        else return false;
    } else if (flag == 2) {
        if (point_on_line(x1, y1, x3, y3, x4, y4) || point_on_line(x2, y2, x3, y3, x4, y4))
            return true;
        else return false;
    } else return false;
}


int orientation(Point const& a, Point const& b, Point const& c) {
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

bool point_belong(std::vector<Point> const& a, Point const& b) {
    int num_intersections = 0;
    for (int i = 0; i != a.size(); ++i) {
        Point min_point = a[i];
        Point max_point = a[(i + 1) % a.size()];
        if (min_point.y > max_point.y)
            std::swap(min_point, max_point);
        if (max_point.y <= b.y || min_point.y > b.y) continue;
        if (point_on_line(b.x, b.y, min_point.x, min_point.y, max_point.x, max_point.y)) return true;
        if (intersect(min_point.x, min_point.y, max_point.x, max_point.y, b.x, b.y, 100000, b.y))
            ++num_intersections;
    }
    return num_intersections % 2;
}


int main() {
    int n;
    std::cin >> n;
    Point point{};
    std::cin >> point.x >> point.y;

    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) std::cin >> points[i].x >> points[i].y;

    if (point_belong(points, point)) std::cout << "YES";
    else std::cout << "NO";
    return 0;
}
