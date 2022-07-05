#include <iostream>
#include <vector>
#include <algorithm>

void dfs(size_t now, std::vector<std::vector<size_t>>& g,
         std::vector<size_t>& visited, bool& flag) {
    for (size_t neig : g[now]) {
        if (visited[neig] == 0) {
            visited[neig] = 3 - visited[now];
            dfs(neig, g, visited, flag);
        } else if (visited[neig] == visited[now]) {
            flag = false;
            break;
        }
    }
}

void find_comps(std::vector<std::vector<size_t>>& g, std::vector<size_t>& visited, bool& flag) {
    for (size_t i = 1; i < visited.size(); ++i) {
        if (visited[i] == 0) {
            visited[i] = 1;
            dfs (i, g, visited, flag);
            if (!flag) {
                break;
            }
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

    std::vector<size_t> visited(v + 1, 0);
    bool flag = true;
    find_comps(table, visited, flag);

    if (flag) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
