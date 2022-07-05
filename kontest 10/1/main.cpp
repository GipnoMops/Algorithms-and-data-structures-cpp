#include <iostream>
#include <vector>
#include <algorithm>

void dfs(size_t now, std::vector<std::vector<int>>& g,
         std::vector<bool>& visited, std::vector<int>& vec) {
    visited[now] = true;
    vec.push_back(now);
    for (size_t neig : g[now]) {
        if (!visited[neig]) {
            dfs(neig, g, visited, vec);
            vec.push_back(now);
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> table(n + 1);
    int root = 0;
    for (int i = 1; i <= n; ++i) {
        int top;
        std::cin >> top;
        if (top == 0) {
            root = i;
            continue;
        }
        table[top].push_back(i);
        table[i].push_back(top);
    }

    std::vector<bool> visited(n + 1, false);
    std::vector<int> vec;
    dfs(root, table, visited, vec);

    /*std::cout << vec.size() << "\n";
    for (auto elem : vec)
        std::cout << elem << " ";
    std::cout << "\n";*/

    std::vector<int> first(n + 1, -1), last(n + 1, -1);
    for (int i = 0; i < vec.size(); ++i) {
        int elem = vec[i];
        if (first[elem] == -1) first[elem] = i;
        last[elem] = i;
    }

    /*for (auto elem : first) std::cout << elem << " ";
    std::cout << "\n";
    for (auto elem : last) std::cout << elem << " ";
    std::cout << "\n";*/

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int top1, top2;
        std::cin >> top1 >> top2;
        if (first[top1] < first[top2] && last[top1] > last[top2]) std::cout << "1\n";
        else std::cout << "0\n";
    }

    return 0;
}
