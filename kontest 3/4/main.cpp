#include <iostream>
#include <vector>
#include <queue>


int bfs(int start, std::vector<std::vector<int>>& g, std::vector<int>& fleas) {
    std::vector<int> distance(g.size(), g.size() + 1);
    std::vector<int> visited(g.size());
    std::queue<int> q;
    q.push(start);
    distance[start] = 0;
    visited[start] = true;
    int v = 0;

    while(!q.empty()) {
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

    int ansver = 0;
    for (auto& elem : fleas) {
        if (distance[elem] >= g.size() + 1) {
            return -1;
        }
        ansver += distance[elem];
    }
    return ansver;
}

int main() {
    int n, m, s, t, q;
    std::cin >> n >> m >> s >> t >> q;
    std::vector<std::vector<int>> table(n * m + 1);
    std::vector<int> fleas;
    for (int i = 0; i < q; ++i) {
        int x, y;
        std::cin >> x >> y;
        fleas.push_back((x - 1) * m + y);
    }

    int num;
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            num = (x - 1) * m + y;
            if (x - 2 > 0 && y - 1 > 0) {
                table[(x - 3) * m + y - 1].push_back(num);
                table[num].push_back((x - 3) * m + y - 1);
            }
            if (x - 1 > 0 && y - 2 > 0) {
                table[(x - 2) * m + y - 2].push_back(num);
                table[num].push_back((x - 2) * m + y - 2);
            }
            if (x + 1 <= n && y - 2 > 0) {
                table[x * m + y - 2].push_back(num);
                table[num].push_back(x * m + y - 2);
            }
            if (x + 2 <= n && y - 1 > 0) {
                table[(x + 1) * m + y - 1].push_back(num);
                table[num].push_back((x + 1) * m + y - 1);
            }
            if (x + 2 <= n && y + 1 <= m) {
                table[(x + 1) * m + y + 1].push_back(num);
                table[num].push_back((x + 1) * m + y + 1);
            }
            if (x + 1 <= n && y + 2 <= m) {
                table[x * m + y + 2].push_back(num);
                table[num].push_back(x * m + y + 2);
            }
            if (x - 1 > 0 && y + 2 <= m) {
                table[(x - 2) * m + y + 2].push_back(num);
                table[num].push_back((x - 2) * m + y + 2);
            }
            if (x - 2 > 0 && y + 1 <= m) {
                table[(x - 3) * m + y + 1].push_back(num);
                table[num].push_back((x - 3) * m + y + 1);
            }
        }
    }
    std::cout << bfs((s - 1) * m + t, table, fleas);
    return 0;
}
