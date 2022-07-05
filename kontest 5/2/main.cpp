#include <iostream>
#include <vector>

bool cycle_check (size_t now, std::vector<std::vector<size_t>>& g, std::vector<size_t>& visited) {
    visited[now] = 1;
    for (auto& neig : g[now]) {
        if (visited[neig] == 0) {
            if (cycle_check(neig, g, visited)) return true;
        } else if (visited[neig] == 1) {
            return true;
        }
    }
    visited[now] = 2;
    return false;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<size_t>> g(n + 1);

    int leen;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> leen;
            if (leen > 0)
                g[i].push_back(j);
        }
    }

    bool flag = false;
    std::vector<size_t> visited(g.size(), 0);
    for (size_t i = 1; i <= visited.size(); ++i) {
        if (visited[i] == 0 && cycle_check(i, g, visited)) {
            flag = true;
            break;
        }
    }
    std::cout << flag;
    return 0;
}
