#include <iostream>
#include <vector>

void dfs (int v, int l, int& timer, std::vector <std::vector<int>>& g,
          std::vector<int>& tin, std::vector<int>& tout,
          std::vector<std::vector<int>>& up, std::vector<std::vector<int>>& count, int p = 0) {
    tin[v] = ++timer;
    up[v][0] = p;
    ++count[v][0];
    for (int i = 1; i <= l; ++i) {
        up[v][i] = up[up[v][i-1]][i-1];
        ++count[v][i];
    }
    for (auto to : g[v]) {
        if (to != p)
            dfs (to, l, timer, g, tin, tout, up, count, v);
    }
    tout[v] = ++timer;
}

bool upper (long long int a, long long int b, std::vector<int>& tin, std::vector<int>& tout) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> table(n);
    int root = 0;
    for (int i = 1; i <= n; ++i) {
        int top;
        std::cin >> top;
        if (top == -1) {
            root = i;
            continue;
        }
        table[top].push_back(i);
        table[i].push_back(top);
    }

    std::vector<int> tin(n), tout(n);
    int timer = 0;
    std::vector<std::vector<int>> up(n);
    std::vector<std::vector<int>> count(n, std::vector<int>(n));

    int l = 1;
    while ((1<<l) <= n)  ++l;
    for (int i = 0; i < n; ++i)  up[i].resize (l + 1);
    dfs (root, l, timer, table, tin, tout, up, count);

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int v, k;
        std::cin >> v >> k;
        std::cout << count[--v][--k] << "\n";
    }
}
