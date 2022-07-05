#include <iostream>
#include <vector>

const double EPS = 1E-9;

struct Point {
    double x, y;
};

bool point_on_line(Point p0, Point p1, Point p2) {
    double x0 = p0.x, y0 = p0.y;
    double x1 = p1.x, y1 = p1.y;
    double x2 = p2.x, y2 = p2.y;

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

int sgn(double x) {
    if (x >= 0) return 1;
    return -1;
}

bool point_belong2 (Point p, std::vector<Point>& points) {
    if (points.size() == 1) return (p.x == points[0].x && p.y == points[0].y);
    else if (points.size() == 2) return point_on_line(p, points[0], points[1]);

    double x1 = points[0].x, y1 = points[0].y;
    double x2, y2;
    for (int i = 1; i < points.size(); ++i) {
        x2 = points[i].x; y2 = points[i].y;
        if (sgn((p.x - x1) * (y2 - y1) - (x2 - x1) * (p.y - y1)) == 1) return false;
        x1 = x2; y1 = y2;
    }
    if (sgn((p.x - x2) * (points[0].y - y2) - (points[0].x - x2) * (p.y - y2)) == 1) return false;
    return true;
}


int main() {
    int n;
    std::cin >> n;
    Point point{};
    std::cin >> point.x >> point.y;

    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) std::cin >> points[i].x >> points[i].y;

    if (point_belong2(point, points)) std::cout << "YES";
    else std::cout << "NO";
}
