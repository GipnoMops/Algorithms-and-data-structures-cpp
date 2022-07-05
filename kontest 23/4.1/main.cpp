#include <iostream>

const double EPS = 1E-9;

int sgn (double x) {
    if (x >= 0.0) return 1;
    else return -1;
}

bool point_on_line (double x0, double y0, double x1, double y1, double x2, double y2) {

    if ((x0 == x1 && y0 == y1) || (x0 == x2 && y0 == y2)) return true;
    if (x0 * (y2 - y1) + y0 * (x1 - x2) + (y1 * x2 - x1 * y2) <= EPS) {
        if ((y2 - y1 >= EPS && y0 - y1 >= EPS && y0 - y2 <= EPS) ||
        (y2 - y1 <= EPS && y0 - y1 <= EPS && y0 - y2 >= EPS)) {
            if (y1 == y0 == y2) {
                if ((x2 >= x1 && x0 >= x1 && x0 <= x2) || (x2 <= x1 && x0 <= x1 && x0 >= x2)) return true;
                else return false;
            } else return true;
        } else return false;
    } else return false;

}

int main() {
    double x1, x2, y1, y2, x3, x4, y3, y4;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    double a1, b1, c1, a2, b2, c2;
    a1 = y2 - y1; b1 = x1 - x2; c1 = y1 * x2 - x1 * y2;
    a2 = y4 - y3; b2 = x3 - x4; c2 = y3 * x4 - x3 * y4;

    int flag;
    double x, y, b3, c3;
    if (a1 * b2 == b1 * a2) {
        if (a1 * c2 == c1 * a2) flag = 2;
        else flag = 0;
    } else {
        flag = 1;
        b3 = b1 * a2 - b2 * a1, c3 = c1 * a2 - c2 * a1;
        x = c3 * b2 - c2 * b3;
        y = -1 * c3;
        if (y == -1 * 0.0) y = 0.0;
        if (x == -1 * 0.0) x = 0.0;
    }

    if (flag == 1) {
        if (sgn((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) !=
        sgn((x2 - x1) * (y4 - y1) - (x4 - x1) * (y2 - y1)) &&
        sgn((x4 - x3) * (y1 - y3) - (x1 - x3) * (y4 - y3)) !=
        sgn((x4 - x3) * (y2 - y3) - (x2 - x3) * (y4 - y3))) std::cout << "YES";
        else std::cout << "NO";

    } else if (flag == 2) {
        if (point_on_line(x1, y1, x3, y3, x4, y4) || point_on_line(x2, y2, x3, y3, x4, y4))
            std::cout << "YES";
        else std::cout << "NO";
    } else std::cout << "NO";

    return 0;
}
