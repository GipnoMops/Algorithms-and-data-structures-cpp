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


/*
 *
7
0 1 0 0 0 0 0
1 0 1 0 0 0 0
0 1 0 1 0 0 0
0 0 1 0 1 0 1
0 0 0 1 0 1 0
0 0 0 0 1 0 1
0 0 0 1 0 0 0
*/
