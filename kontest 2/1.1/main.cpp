#include <iostream>
#include <vector>
#include <algorithm>

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

void dfs (size_t now, std::vector<std::vector<size_t>>& g, std::vector<size_t>& ans, std::vector<bool>& used) {
    used[now] = true;
    for (auto& neig : g[now]) {
        if (!used[neig])
            dfs (neig, g, ans, used);
    }
    ans.push_back(now);
}

void topological_sort(std::vector<std::vector<size_t>>& g) {
    std::vector<size_t> visited(g.size(), 0);
    std::vector<size_t> ans;
    std::vector<bool> used(g.size(), false);
    for (size_t i = 1; i < used.size(); ++i) {
        if (cycle_check(i, g, visited)) {
            std::cout << "-1\n";
            exit(0);
        }

        if (!used[i]) {
            dfs (i, g, ans, used);
        }
    }
    std::reverse(ans.begin(), ans.end());

    for (auto& elem : ans) {
        std::cout << elem << " ";
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

    topological_sort(table);
    return 0;
}


/*
 * 4 4
1 2
2 3
3 4
2 4
 */