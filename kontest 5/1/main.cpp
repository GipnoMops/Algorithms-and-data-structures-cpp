#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 50000001;

int main() {
    int v;
    std::cin >> v;
    std::vector<std::vector<int>> g(v + 1, std::vector<int>(v + 1));

    int leen;
    for (int i = 1; i <= v; ++i) {
        for (int j = 1; j <= v; ++j) {
            std::cin >> leen;
            if (leen != 0)
                g[i][j] = leen;
            else
                g[i][j] = 0;
        }
    }


    for (size_t k = 1; k <= v; ++k)
        for (size_t from = 1; from <= v; ++from)
            for (size_t to = 1; to <= v; ++to)
                g[from][to] = std::min(g[from][to], g[from][k] + g[k][to]);

    int max = 0;
    for (size_t i = 1; i <= v; ++i) {
        for (size_t j = 1; j <= v; ++j) {
            if (g[i][j] != INF)
                max = std::max(max, g[i][j]);
        }
    }
    std::cout << max;
    return 0;
}
