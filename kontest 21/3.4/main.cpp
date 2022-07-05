#include <iostream>
#include <vector>

int INF = 2147483647;

int find_path(std::vector<std::vector<int>>& cap, std::vector<bool>& vis, int u, int t, int f) {
    if (u == t) return f;
    vis[u] = true;
    for (int v = 0; v < vis.size(); ++v)
        if (!vis[v] && cap[u][v] > 0) {
            int df = find_path(cap, vis, v, t, std::min(f, cap[u][v]));
            if (df > 0) {
                cap[u][v] -= df; cap[v][u] += df;
                return df;
            }
        }
    return 0;
}


int max_flow(std::vector<std::vector<int>>& cap, int s, int t) {
    int flow = 0;
    std::vector<bool> vis(cap.size() , false);
    while (true) {
        vis.assign(vis.size(), false);
        int df = find_path(cap, vis, s, t, INF);
        if (df == 0) return flow;
        flow += df;
    }
}


int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> capacity(n, std::vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        int u, v, cap;
        std::cin >> u >> v >> cap;
        capacity[u - 1][v - 1] = cap;
        capacity[v - 1][u - 1] = cap;
    }
    std::cout << max_flow(capacity, 0, n - 1);
    return 0;
}