#include <iostream>

int main() {
    double x1, x2, y1, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << y2 - y1 << " " << x1 - x2 << " " << y1 * x2 - x1 * y2;
    return 0;
}
