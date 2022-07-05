#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x, y;
};

bool compare (Point& a, Point& b) {
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool check2 (Point& a, Point& b, Point& c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

bool check3 (Point& a, Point& b, Point& c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

void convex_hull (std::vector<Point>& points) {
    if (points.size() == 1)  return;
    sort (points.begin(), points.end(), &compare);
    Point p1 = points[0],  p2 = points.back();
    std::vector<Point> up, down;
    up.push_back (p1); down.push_back (p1);
    for (size_t i = 1; i < points.size(); ++i) {
        if (i == points.size() - 1 || check3(p1, points[i], p2)) {
            while (up.size() >= 2 && !check3(up[up.size() - 2], up[up.size() - 1], points[i]))
                up.pop_back();
            up.push_back (points[i]);
        }
        if (i == points.size() - 1 || check2(p1, points[i], p2)) {
            while (down.size() >= 2 && !check2(down[down.size() - 2], down[down.size() - 1], points[i]))
                down.pop_back();
            down.push_back (points[i]);
        }
    }
    points.clear();
    for (auto& i : up) points.push_back (i);
    for (size_t i = down.size() - 2; i > 0; --i)
        points.push_back(down[i]);
}

std::pair<double, double> square_ans_perimeter(std::vector<Point>& points) {
    int n = (int)points.size();
    double x = points[0].x, y = points[0].y;
    double x1 = x, y1 = y;

    double square = 0, perimeter = 0, x2, y2;
    for (int i = 1; i < n; ++i) {
        x2 = points[i].x; y2 = points[i].y;
        perimeter += std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        square += (x1 + x2) * (y2 - y1);
        x1 = x2; y1 = y2;
    }
    perimeter += std::sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
    square += (x + x2) * (y - y2);
    return std::make_pair(std::abs(square) / 2, perimeter);
}


int main() {
    int n;
    std::cin >> n;
    std::vector<Point> points;
    for (int i = 0; i < n; ++i) {
        Point p{};
        std::cin >> p.x >> p.y;
        points.push_back(p);
    }

    convex_hull(points);
    auto answer = square_ans_perimeter(points);
    std::cout << answer.second << "\n" << answer.first;
    return 0;
}
