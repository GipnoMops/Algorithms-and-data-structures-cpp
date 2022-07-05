#include <iostream>
#include <vector>

struct Point {
    int x;
    int y;
};


int main() {
    int n;
    Point point{};
    std::cin >> n >> point.x >> point.y;
    std::vector<Point> points;
    for (int i = 0; i < n; ++i) {
        Point p{};
        std::cin >> p.x >> p.y;
        points.push_back(p);
    }

    bool result = false;
    int j = n - 1;
    for (int i = 0; i < n; ++i) {
        if ((points[i].y < points[j].y && points[i].y <= point.y && point.y <= points[j].y &&
        ((points[j].y - points[i].y) * (point.x - points[i].x) > (points[j].x - points[i].x) * (point.y - points[i].y)))
        || (points[i].y > points[j].y && points[j].y <= point.y && point.y <= points[i].y &&
        ((points[j].y - points[i].y) * (point.x - points[i].x) < (points[j].x - points[i].x) * (point.y - points[i].y))))
            result = !result;
        j = i;
    }


    if (result) std::cout << "YES";
    else std::cout << "NO";
    return 0;
}
