#include <iostream>
#include <vector>

struct Point {
    double x, y;
};

struct Angle {
    double a, b;
};

bool operator < (const Angle& p, const Angle& q) {
    if (p.b == 0 && q.b == 0)
        return p.a < q.a;
    return p.a * 1ll * q.b < p.b * 1ll * q.a;
}

long double sq (Point & a, Point & b, Point & c) {
    return a.x * 1ll * (b.y - c.y) + b.x * 1ll * (c.y - a.y) + c.x * 1ll * (a.y - b.y);
}

bool point_belong(Point& point, std::vector<Point>& points) {
    int n = (int)points.size();

    int zero_id = 0;
    for (int i = 0; i < n; ++i) {
        if (points[i].x < points[zero_id].x ||
            points[i].x == points[zero_id].x &&
            points[i].y < points[zero_id].y)
            zero_id = i;
    }

    Point zero = points[zero_id];
    rotate(points.begin(), points.begin() + zero_id, points.end());
    points.erase(points.begin()); --n;

    std::vector<Angle> angles(n);
    for (int i = 0; i < n; ++i) {
        angles[i].a = points[i].y - zero.y;
        angles[i].b = points[i].x - zero.x;
        if (angles[i].a == 0)
            angles[i].b = angles[i].b < 0 ? -1 : 1;
    }

    bool answer = false;
    if (point.x >= zero.x) {
        if (point.x == zero.x && point.y == zero.y)
            answer = true;
        else {
            Angle my = {point.y - zero.y, point.x - zero.x};
            if (my.a == 0)
                my.b = my.b < 0 ? -1 : 1;
            auto it = upper_bound(angles.begin(), angles.end(), my);
            if (it == angles.end() && my.a == angles[n - 1].a && my.b == angles[n - 1].b)
                it = angles.end() - 1;
            if (it != angles.end() && it != angles.begin()) {
                int p1 = int(it - angles.begin());
                if (sq(points[p1], points[p1 - 1], point) <= 0)
                    answer = true;
            }
        }
    }
    return answer;
}


int main() {
    int n;
    std::cin >> n;
    Point point{};
    std::cin >> point.x >> point.y;

    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) std::cin >> points[i].x >> points[i].y;

    if (point_belong(point, points)) std::cout << "YES";
    else std::cout << "NO";
}
