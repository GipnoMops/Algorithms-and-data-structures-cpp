#include <iostream>
#include <vector>

const int INF = (int) 1e9;


void add(int u, int v, int cap, std::vector<int>& on_end, std::vector<int>& next,
             std::vector<int>& first, std::vector<int>& capacity, int& count) {
    on_end[count] = v;
    next[count] = first[u];
    first[u] = count;
    capacity[count++] = cap;

    on_end[count] = u;
    next[count] = first[v];
    first[v] = count;
    capacity[count++] = 0;
}


int find_flow(int u, int flow, int m, std::vector<int>& visited, std::vector<int>& first,
             std::vector<int>& next, std::vector<int>& on_end, std::vector<int>& capacity) {
    if (u == m - 1) return flow;
    visited[u] = true;
    for (int edge = first[u]; edge != -1; edge = next[edge]) {
        int to = on_end[edge];
        if (!visited[to] && capacity[edge] > 0) {
            int minResult = find_flow(to, std::min(flow, capacity[edge]), m, visited,
                                     first,next, on_end, capacity);
            if (minResult > 0) {
                capacity[edge] -= minResult;
                capacity[edge ^ 1] += minResult;
                return minResult;
            }
        }
    }
    return 0;
}


int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> capacity(2 * m), on_end(2 * m), next(2 * m);
    std::vector<int> first(2 * n, -1), visited(2 * n);
    int count = 0;
    for (int i = 0; i < m; ++i) {
        int u, v, cap;
        std::cin >> u >> v >> cap;
        add(u, v, cap, on_end, next, first, capacity, count);
    }

    int max = 0, result;
    while ((result = find_flow(1, INF, m, visited, first, next, on_end, capacity)) > 0) {
        visited.assign(n, false);
        max += result;
    }
    std::cout << max << "\n";
    return 0;
}
