#include <iostream>
#include <vector>
#include <queue>

int bfs(size_t start, size_t end, std::vector<std::vector<size_t>>& g) {
    std::vector<size_t> distance(g.size(), g.size() + 1);
    std::vector<size_t> visited(g.size());
    std::queue<size_t> q;
    q.push(start);
    distance[start] = 0;
    visited[start] = true;
    size_t v = 0;

    while(!q.empty() && v != end) {
        int v = q.front();
        q.pop();
        for (auto& neig : g[v]) {
            if (!visited[neig]) {
                visited[neig] = true;
                q.push (neig);
                distance[neig] = distance[v] + 1;
            }
        }
    }

    if (distance[end] > g.size()) {
        return -1;
    } else {
        return distance[end];
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
    size_t start, end;
    std::cin >> start >> end;
    std::cout << bfs(start, end, table) << "\n";
    return 0;
}
