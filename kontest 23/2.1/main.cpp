#include <iostream>

int main() {
    double x1, x2, y1, y2, x0, y0;
    std::cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
    if (x0 * (y2 - y1) + y0 * (x1 - x2) + (y1 * x2 - x1 * y2) == 0.0) {
        if ((y2 >= y1 && y0 >= y1) || (y2 <= y1 && y0 <= y1)) {
            if (y1 == y0 == y2) {
                if ((x2 >= x1 && x0 >= x1) || (x2 <= x1 && x0 <= x1)) std::cout << "YES";
                else std::cout << "NO";
            } else std::cout << "YES";
        } else std::cout << "NO";
    } else std::cout << "NO";
    return 0;
}
