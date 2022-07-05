#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 10000000;

void dfs (int v, int l, int& timer, std::vector<std::vector<int>>& g,
          std::vector<int>& tin, std::vector<int>& tout,
          std::vector<std::vector<std::pair<int, int>>>& up, int p = 0) {
    tin[v] = ++timer;
    up[v][0] = std::make_pair(p, g[v][p]);
    for (int i = 1; i <= l; ++i)
        up[v][i] = std::make_pair(up[up[v][i-1].first][i-1].first,
                                  std::min(up[up[v][i-1].first][i-1].second, up[v][i].second));
    for (auto to : g[v]) {
        if (to != p && to != INF)
            dfs (to, l, timer, g, tin, tout, up, v);
    }
    tout[v] = ++timer;
}

bool upper (int a, int b, std::vector<int>& tin, std::vector<int>& tout) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b, int l, std::vector<std::vector<int>>& g,
                         std::vector<int>& tin, std::vector<int>& tout,
                         std::vector<std::vector<std::pair<int, int>>>& up) {
    int min = -10000000;
    if (upper(a, b, tin, tout)) {
        int top = b;
        while (top != a) {
            min = std::min(min, g[top][up[top][0].first]);
            top = up[top][0].first;
        }
        return min;
    }
    if (upper(b, a, tin, tout)) {
        int top = a;
        while (top != b) {
            min = std::min(min, g[top][up[top][0].first]);
            top = up[top][0].first;
        }
        return min;
    }
    for (int i = l; i >= 0; --i)
        if (!upper (up[a][i].first, b, tin, tout)) {
            min = std::min(min, up[a][i].second);
            a = up[a][i].first;
        }
    return min;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> table(n + 1, std::vector<int>(n + 1, INF));
    for (int i = 2; i < n + 1; ++i) {
        int top, wei;
        std::cin >> top >> wei;
        table[top][i] = wei;
        table[i][top] = wei;
    }

    std::vector<int> tin(n + 1), tout(n + 1);
    int timer = 0;
    std::vector<std::vector<std::pair<int, int>>> up(n + 1);

    int l = 1;
    while ((1<<l) <= n)  ++l;
    for (int i = 0; i < n; ++i)  up[i].resize (l + 1);
    dfs (1, l, timer, table, tin, tout, up);

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        std::cout << std::min(lca(x, y, l, table, tin, tout, up),
                              lca(y, x, l, table, tin, tout, up)) << "\n";
    }
}
