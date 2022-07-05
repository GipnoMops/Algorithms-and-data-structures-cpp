#include <iostream>
#include <vector>
#include <algorithm>

void dfs(size_t now,  std::vector<std::vector<size_t>>& graph,
         bool is_root, std::vector<bool>& visited,
         size_t& time, std::vector<size_t>& tin, std::vector<size_t>& childs,
         std::vector<size_t>& up, std::vector<bool>& ap) {
    visited[now] = true;
    ++time;
    tin[now] = time;
    for (auto neig : graph[now]) {
        if (!visited[neig]) {
            ++childs[now];
            dfs(neig, graph, false, visited, time, tin, childs, up, ap);
            up[now] = std::min(up[now], up[neig]);
            if (up[neig] >= tin[now] && !is_root)
                ap[now] = true;
        } else {
            up[now] = std::min(up[now], tin[neig]);
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
    std::vector<bool> ap(v + 1, false);
    size_t time = 0;
    std::vector<size_t> tin(v + 1);
    std::vector<size_t> childs(v + 1);
    std::vector<size_t> up(v + 1, v + 1);

    for (size_t now = 1; now <= v; ++now) {
        time = 0;
        if (!visited[now]) {
            dfs(now, table, true, visited, time, tin, childs, up, ap);
            if (childs[now] >= 2)
                ap[now] = true;
        }
    }

    std::cout << std::count(ap.begin(), ap.end(), true) << "\n";
    for (size_t i = 0; i < ap.size(); ++i) {
        if (ap[i]) {
            std::cout << i << "\n";
        }
    }
    return 0;
}
