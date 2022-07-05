#include <iostream>
#include <vector>
#include <algorithm>

void dfs(size_t now, std::vector<std::vector<size_t>>& g, std::vector<bool>& visited) {
    visited[now] = true;
    for (size_t neig : g[now]) {
        if (!visited[neig]) {
            dfs(neig, g, visited);
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
   dfs(1, table, visited);

   std::cout << std::count(visited.begin(), visited.end(), true) << "\n";
   for (size_t i = 0; i <= v; ++i) {
       if (visited[i]) {
           std::cout << i << " ";
       }
   }
   return 0;
}
