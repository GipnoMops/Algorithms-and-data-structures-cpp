#include <iostream>
#include <iomanip>

int main() {
    double x1, x2, y1, y2, x3, x4, y3, y4;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    double a1, b1, c1, a2, b2, c2;
    a1 = y2 - y1; b1 = x1 - x2; c1 = y1 * x2 - x1 * y2;
    a2 = y4 - y3; b2 = x3 - x4; c2 = y3 * x4 - x3 * y4;
    if (a1 * b2 == b1 * a2) {
        if (a1 * c2 == c1 * a2) std::cout << 2;
        else std::cout << 0;
    } else {
        std::cout << 1 << " ";
        double b3 = b1 * a2 - b2 * a1, c3 = c1 * a2 - c2 * a1;
        double x = (c3 * b2 - c2 * b3) / (a2 * b3);
        double y = -1 * (c3 / b3);
        if (y == -1 * 0.0) y = 0.0;
        if (x == -1 * 0.0) x = 0.0;
        std::cout<<std::fixed<<std::setprecision(2)<< x << " " << y;
    }
    return 0;
}
