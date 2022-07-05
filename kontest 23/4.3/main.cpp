#include <iostream>
#include <cmath>

bool point_on_line (double x0, double y0, double x1, double y1, double x2, double y2) {

    if ((x0 == x1 && y0 == y1) || (x0 == x2 && y0 == y2)) return true;
    if (x0 * (y2 - y1) + y0 * (x1 - x2) + (y1 * x2 - x1 * y2) == 0.0) {
        if ((y2 >= y1 && y0 >= y1 && y0 <= y2) || (y2 <= y1 && y0 <= y1 && y0 >= y2)) {
            if (y1 == y0 == y2) {
                if ((x2 >= x1 && x0 >= x1 && x0 <= x2) || (x2 <= x1 && x0 <= x1 && x0 >= x2)) return true;
                else return false;
            } else return true;
        } else return false;
    } else return false;

}

int main() {
    double x1, y1, x2, y2, x3, y3, x4, y4, det;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    det = (y4 - y3) * (x1 - x2) - (x4 - x3) * (y1 - y2);
    if (det == 0) {
        if ((x1 * y2 - x2 * y1) * (x4 - x3) - (x3 * y4 - x4 * y3) * (x2 - x1) == 0 &&
            (x1 * y2 - x2 * y1) * (y4 - y3) - (x3 * y4 - x4 * y3) * (y2 - y1) == 0)
            std::cout << "YES";
        else std::cout << "NO";
    } else {
        if (point_on_line(x1, y1, x3, y3, x4, y4) || point_on_line(x2, y2, x3, y3, x4, y4)) std::cout << "YES";
        else std::cout << "NO";
    }
    return 0;
}
