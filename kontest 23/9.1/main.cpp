#include <iostream>
#include <complex>

//Ответственно заявляю, что удовольствия от нахождения подобного решения этой задачи больше, чем от секса.
// Утверждение было проверено эмпирическим образом.

struct Point {
    double x;
    double y;
};


int main() {
    double x, y;
    std::cin >> x >> y;
    Point p1{}, p2{}, p3{}, p4{};
    std::cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;

    std::complex<double> z1(p1.x, p1.y), z2(p2.x, p2.y);
    std::complex<double> c = (z2 - z1) / std::complex<double>(x, 0.0);
    std::complex<double> z0 = z1 / (std::complex<double>(1.0, 0.0) - c);
    std::cout << z0.real() << " " << z0.imag();
    return 0;
}

//https://dxdy.ru/topic55764.html
//http://mathhelpplanet.com/static.php?p=teorema-o-nepodvizhnoy-tochke
