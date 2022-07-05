#include <vector>
#include <iostream>


bool try_kuhn (int v, std::vector<std::vector<int>>& g, std::vector<char>& used, std::vector<int>& mt) {
    if (used[v]) return false;
    used[v] = true;
    for (auto to : g[v]) {
        if (mt[to] == -1 || try_kuhn (mt[to], g, used, mt)) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        while (v != 0) {
            g[i].push_back(v - 1);
            std::cin >> v;
        }
    }

    int counter = 0;
    std::vector<char> used;
    std::vector<int> mt(m, -1);
    for (int v = 0; v < n; ++v) {
        used.assign (n, false);
        if (try_kuhn(v, g, used, mt)) ++counter;
    }

    std::cout << counter << "\n";
    for (int i = 0; i < m; ++i) {
        if (mt[i] != -1) std::cout << mt[i] + 1 << " " << i + 1 << "\n";
    }
}
