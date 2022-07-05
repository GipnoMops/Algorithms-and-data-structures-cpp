#include <iostream>
#include <vector>
#include <algorithm>

void dfs(size_t now, std::vector<std::vector<size_t>>& g,
         std::vector<bool>& visited, std::vector<size_t>& comp) {
    visited[now] = true;
    comp.push_back(now);
    for (size_t neig : g[now]) {
        if (!visited[neig]) {
            dfs(neig, g, visited, comp);
        }
    }
}

void find_comps(std::vector<std::vector<size_t>>& g, std::vector<bool>& visited,
                std::vector<std::vector<size_t>>& connectivity_components) {
    for (size_t i = 1; i < visited.size(); ++i) {
        std::vector<size_t> comp;
        if (!visited[i]) {
            comp.clear();
            dfs (i, g, visited, comp);
            connectivity_components.push_back(comp);
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
    std::vector<std::vector<size_t>> connectivity_components;
    find_comps(table, visited, connectivity_components);

    std::cout << connectivity_components.size() << "\n";
    for (auto& vec : connectivity_components) {
        std::cout << vec.size() << "\n";
        for (auto elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
