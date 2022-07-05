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

void dfs(size_t now, std::vector<std::vector<size_t>>& g,
         std::vector<bool>& visited, std::vector<size_t>& ansver) {
    visited[now] = true;
    for (size_t neig : g[now]) {
        if (!visited[neig]) {
            dfs(neig, g, visited, ansver);
        }
    }
    ansver.push_back(now);
}

void topological_sort(std::vector<std::vector<size_t>>& g, std::vector<size_t>& visited1,
                      std::vector<size_t>& ansver) {
    if (!cycle_check(1, g, visited1)) {
        std::vector<bool> visited(visited1.size(), false);
        for (size_t i = 1; i < visited.size(); ++i) {
            if (!visited[i]) {
                visited[i] = true;
                dfs (i, g, visited, ansver);
            }
        }
        std::reverse(ansver.begin(), ansver.end());

        for (auto& elem : ansver) {
            std::cout << elem << " ";
        }
    } else {
        std::cout << "-1\n";
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

    std::vector<size_t> visited(v + 1, 0);
    std::vector<size_t> ansver;
    topological_sort(table, visited, ansver);
    return 0;
}



/*
#include <iostream>
#include <vector>
#include <algorithm>

void dfs(size_t now, std::vector<std::vector<size_t>>& g,
         std::vector<size_t>& visited, size_t& flag, std::vector<size_t>& cycle, size_t& previous) {
    for (size_t neig : g[now]) {
        if (flag == -1) {
            break;
        }

        if (visited[neig] == 0) {
            visited[neig] = 1;
            dfs(neig, g, visited, flag, cycle, now);
        } else if (neig != previous) {
            flag = neig;
        }

        if (flag == -1) {
            break;
        }
        if (flag > 0) {
            cycle.push_back(now);
            visited[now] = 2;
            if (flag == now) {
                flag = -1;
            }
            break;
        }
    }
    visited[now] = 2;
}

void find_comps(std::vector<std::vector<size_t>>& g, std::vector<size_t>& visited,
                std::vector<size_t>& cycle) {
    size_t flag = 0;
    for (size_t i = 1; i < visited.size(); ++i) {
        size_t previous = 0;
        if (visited[i] == 0) {
            visited[i] = 1;
            dfs (i, g, visited, flag, cycle, previous);
            if (flag == -1) {
                break;
            }
        }
    }
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::vector<size_t>> table(n + 1);
    size_t top;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cin >> top;
            if (top == 1) {
                table[i + 1].push_back(j + 1);
            }
        }
    }

    std::vector<size_t> visited(n + 1, 0);
    std::vector<size_t> cycle;
    find_comps(table, visited, cycle);

    if (!cycle.empty()) {
        std::cout << "YES\n" << cycle.size() << "\n";
        for (auto& elem : cycle) {
            std::cout << elem << " ";
        }
    } else {
        std::cout << "NO";
    }
    return 0;
}
*/