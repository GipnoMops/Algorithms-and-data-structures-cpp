#include <iostream>
#include <vector>

const int EPS = static_cast<const int>(1E-9);

struct Point {
    int x, y;
};

bool point_on_line(Point p0, Point p1, Point p2) {
    int x0 = p0.x, y0 = p0.y;
    int x1 = p1.x, y1 = p1.y;
    int x2 = p2.x, y2 = p2.y;

    if ((x0 == x1 && y0 == y1) || (x0 == x2 && y0 == y2)) return true;
    if (x0 * (y2 - y1) + y0 * (x1 - x2) + (y1 * x2 - x1 * y2) == 0) {
        if ((y2 - y1 >= 0 && y0 - y1 >= 0 && y0 - y2 == 0) ||
            (y2 - y1 <= 0 && y0 - y1 <= 0 && y0 - y2 == 0)) {
            if (y1 == y0 == y2) {
                if ((x2 >= x1 && x0 >= x1 && x0 <= x2) || (x2 <= x1 && x0 <= x1 && x0 >= x2)) return true;
                else return false;
            } else return true;
        } else return false;
    } else return false;

}

int orientation(Point const& a, Point const& b, Point const& c) {
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

bool point_belong(std::vector<Point> const& a, Point const& b) {
    if (a.size() == 1) return (b.x == a[0].x && b.y == a[0].y);
    else if (a.size() == 2) return point_on_line(b, a[0], a[1]);
    int num_intersections = 0;
    for (int i = 0; i < a.size(); ++i) {
        Point min_point = a[i];
        Point max_point = a[(i + 1) % a.size()];
        if (min_point.y == max_point.y) continue;                                           //2
        if (min_point.y > max_point.y)
            std::swap(min_point, max_point);
        if (max_point.y < b.y || min_point.y >= b.y) continue;                              //4
        if (b.y == max_point.y && b.x < std::min(min_point.x, max_point.x)) {               //3
            ++num_intersections; continue;
        }
        int orient = orientation(min_point, max_point, b);
        if (-1 * EPS <= orient <= EPS) return true;                                        //1
        if (orient > 0) ++num_intersections;                                               //5
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
