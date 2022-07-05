#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

void dfs(size_t now, std::vector<std::vector<size_t>>& g,
         std::vector<bool>& visited, std::vector<size_t>& comp, bool& flag) {
    visited[now] = true;
    for (size_t neig : g[now]) {
        if (neig == 1) {
            comp.push_back(now);
            flag = true;
            break;
        }
        if (!visited[neig]) {
            dfs(neig, g, visited, comp, flag);
            if (flag) {
                comp.push_back(neig);
            }
        }
    }
    if (flag) {
        comp.push_back(now);
    }
}

void find_comps(std::vector<std::vector<size_t>>& g, std::vector<bool>& visited,
                std::vector<std::vector<size_t>>& connectivity_components) {
    for (size_t i = 1; i < visited.size(); ++i) {
        bool flag = false;
        std::vector<size_t> comp;
        if (!visited[i]) {
            comp.clear();
            dfs (i, g, visited, comp, flag);
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
    }

    std::vector<bool> visited(v + 1, false);
    std::vector<std::vector<size_t>> connectivity_components;
    find_comps(table, visited, connectivity_components);

    std::set<size_t> ansver;
    ansver.insert(1);
    for (auto& vec : connectivity_components) {
        for (auto elem : vec) {
            ansver.insert(elem);
        }
    }

    for (auto& elem : ansver) {
        std::cout << elem << " ";
    }
    return 0;
}
