#include <iostream>
#include <vector>

struct Point {
    double x, y;
};

double two_squ(std::vector<Point>& points) {
    int n = (int)points.size();
    double x = points[0].x, y = points[0].y;
    double x1 = x, y1 = y;

    double sum = 0;
    double x2, y2;
    for (int i = 1; i < n; ++i) {
        x2 = points[i].x; y2 = points[i].y;
        sum += (x1 + x2) * (y2 - y1);
        x1 = x2; y1 = y2;
    }
    sum += (x + x2) * (y - y2);
    return std::abs(sum);
}

int main() {
    int n;
    std::cin >> n;
    Point point{};
    std::cin >> point.x >> point.y;

    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) std::cin >> points[i].x >> points[i].y;

    double S1 = two_squ(points);
    double S2 = 0;
    for (int i = 0; i < n - 1; ++i) {
        std::vector<Point> temp{point, points[i], points[i + 1]};
        S2 += two_squ(temp);
    }
    std::vector<Point> temp{point, points[0], points[n - 1]};
    S2 += two_squ(temp);
    if (S2 == S1) std::cout << "YES";
    else std::cout << "NO";
    return 0;
}
