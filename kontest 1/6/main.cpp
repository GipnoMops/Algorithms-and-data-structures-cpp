#include <iostream>
#include <vector>
#include <algorithm>

void dfs(size_t now, std::vector<std::vector<size_t>>& g,
         std::vector<bool>& visited, std::vector<size_t>& counter) {
    visited[now] = true;
    for (size_t neig : g[now]) {
        if (!visited[neig]) {
            dfs(neig, g, visited, counter);
            counter[now] = counter[now] + counter[neig] + 1;
        }
    }
}

int main() {
    size_t v, e;
    std::cin >> v >> e;
    std::vector<std::vector<size_t>> table(v + 1);
    size_t top1 = 0, top2 = 0;
    for (size_t i = 0; i < e; ++i) {
        std::cin >> top1 >> top2;
        if (std::count(table[top1].begin(), table[top1].end(), top2) == 0 && top2 != top1) {
            table[top1].push_back(top2);
        }
        if (std::count(table[top2].begin(), table[top2].end(), top1) == 0 && top2 != top1) {
            table[top2].push_back(top1);
        }

    }

    std::vector<bool> visited(v + 1, false);
    std::vector<size_t> counter(v + 1, 0);
    dfs(1, table, visited, counter);

    for (size_t i = 1; i < counter.size(); ++i) {
        std::cout << counter[i] << " ";
    }
    return 0;
}
