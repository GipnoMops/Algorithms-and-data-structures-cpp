#include <iostream>
#include <iomanip>
#include <cmath>


int main() {
    int n, x, y;
    std::cin >> n >> x >> y;
    int x1 = x, y1 = y;

    double sum = 0;
    int x2, y2;
    for (int i = 0; i < (n - 1); ++i) {
        std::cin >> x2 >> y2;
        sum += (x1 + x2) * (y2 - y1);
        x1 = x2; y1 = y2;
    }
    sum += (x + x2) * (y - y2);
    std::cout << std::fixed << std::setprecision(5) << std::abs(sum) / 2 << "\n";
    return 0;
}