#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

void bfs(size_t start, size_t end, std::vector<std::vector<size_t>>& g) {
    if (end == start) {
        std::cout << 0 << "\n";
        return;
    }

    std::vector<size_t> distance(g.size(), g.size() + 1);
    std::vector<int> p(g.size(), -1);
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
                p[neig] = v;
            }
        }
    }

    if (distance[end] > g.size()) {
        std::cout << "-1\n";
    } else {
        std::vector<size_t> way;
        std::cout << distance[end] << "\n";
        int top = end;
        way.push_back(end);
        while (p[top] != -1) {
            way.push_back(p[top]);
            top = p[top];
        }
        std::reverse(way.begin(), way.end());
        for (auto& elem : way) {
            std::cout << elem << " ";
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
    size_t start, end;
    std::cin >> start >> end;
    bfs(start, end, table);
    return 0;
}
