#include <iostream>
#include <vector>
#include <queue>

const int INF = 100000;

int main() {
    int n, s, f;
    std::cin >> n >> s >> f;
    std::vector<std::vector<std::pair<int,int>>> g(n + 1);

    int leen;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> leen;
            if (leen > 0)
                g[i].push_back(std::make_pair(leen, j));
        }
    }

    std::vector<int> d(n + 1, INF);
    d[s] = 0;
    std::priority_queue <std::pair<int,int>> q;
    q.push(std::make_pair(0, s));
    while (!q.empty()) {
        int v = q.top().second,  cur_d = -q.top().first;
        q.pop();
        if (d[v] >= INF) break;
        if (cur_d > d[v])  continue;

        for (auto& [len, to] : g[v]) {
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.push(std::make_pair(-d[to], to));
            }
        }
    }

    if (d[f] < INF)
        std::cout << d[f];
    else
        std::cout << -1;
}