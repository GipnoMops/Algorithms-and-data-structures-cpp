#include <iostream>

struct Point {
    double x, y;
};

struct Eq_li {
    double a, b, c;
};

int main() {
    Point p1{}, p2{}, p3{}, p4{};
    std::cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;
    Eq_li eq1{p2.y - p1.y, p1.x - p2.x, p1.y * p2.x - p1.x * p2.y};
    Eq_li eq2{p4.y - p3.y, p3.x - p4.x, p3.y * p4.x - p3.x * p4.y};

    int flag;
    if (eq1.a * eq2.b == eq1.b * eq2.a) {
        if (eq1.a * eq2.c == eq1.c * eq2.a) flag = 2;
        else flag = 0;
    } else {
        flag = 1;
        double b3 = eq1.b * eq2.a - eq2.b * eq1.a, c3 = eq1.c * eq2.a - eq2.c * eq1.a;
        double x = (c3 * eq2.b - eq2.c * b3) / (eq2.a * b3);
        double y = -1 * (c3 / b3);
        if (y == -1 * 0.0) y = 0.0;
        if (x == -1 * 0.0) x = 0.0;
    }


    return 0;
}
