#include <vector>
#include <iostream>
#include <algorithm>


void dfs(std::vector<std::vector<int>>& table, std::vector<bool>& marked, int k,
         int vert, int start, int &count) {
    marked[vert] = true;
    if (k == 0) {
        marked[vert] = false;
        if (std::find(table[vert].begin(),
                      table[vert].end(), start) != table[vert].end()) ++count;
        return;
    }

    for (auto neib : table[vert])
        if (!marked[neib])
            dfs(table, marked, k - 1, neib, start, count);
    marked[vert] = false;
}


int countCycles(std::vector<std::vector<int>>& table, int k) {
    std::vector<bool> marked(table.size(), false);
    int count = 0;
    for (int i = 0; i < table.size() - (k - 1); ++i) {
        dfs(table, marked, k - 1, i, i, count);
        marked[i] = true;
    }
    return count / 2;
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    if (n == 1) {
        std::cout << 0;
    } else {
        std::vector<std::vector<int>> table(n);
        for (int i = 0; i < m; ++i) {
            int top_1, top_2;
            std:: cin >> top_1 >> top_2;
            table[top_1].push_back(top_2);
            table[top_2].push_back(top_1);
        }
        std::cout << countCycles(table, 3);
    }
    return 0;
}
