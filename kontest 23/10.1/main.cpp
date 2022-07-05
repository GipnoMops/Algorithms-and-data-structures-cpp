#include <iostream>
#include <vector>

struct Point {
    int x, y;
};
std::vector<Point> points;

struct Equation {
    int a, b, c;
};
std::vector<Equation> equ;

int sgn(int x) {
    if (x > 0) return 1;
    return -1;
}

bool on_one_piece(int j1, int j2, int m) {
    for(int i = 0; i < m; ++i) {
        if(sgn(equ[i].a * points[j1].x + equ[i].b * points[j1].y + equ[i].c) !=
        sgn(equ[i].a * points[j2].x + equ[i].b * points[j2].y + equ[i].c))
            return false;
    }
    return true;
}


int main() {
    int n, m, r;
    std::cin >> n >> m >> r;

    std::vector<int> sort(n);
    for (int i = 0; i < n; ++i) {
        sort[i] = i;
        Point temp{};
        std::cin >> temp.x >> temp.y;
        points.push_back(temp);
    }

    for (int i = 0; i < m; ++i) {
        Equation temp{};
        std::cin >> temp.a >> temp.b >> temp.c;
        equ.push_back(temp);
    }

    std::vector<int> temp_sort(n);
    for (int j = 0; j < m; ++j) {
        int k = 0;

        for (int i = 0; i < n; ++i) {
            if (equ[j].a * points[i].x + equ[j].b * points[i].y + equ[j].c < 0) ++k;
            temp_sort[i] = sort[i];
        }

        int less_id = 0;
        for (int i = 0; i < n; ++i) {
            if (equ[j].a * points[temp_sort[i]].x + equ[j].b * points[temp_sort[i]].y + equ[j].c < 0)
                sort[less_id++] = temp_sort[i];
            else sort[k++] = temp_sort[i];
        }
    }

    for (int i = 1; i < n; ++i) {
        if (on_one_piece(sort[i - 1], sort[i], m)) {
            std::cout << "YES"; return 0;
        }
    }

    std::cout << "NO";
    return 0;
}