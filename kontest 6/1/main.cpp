#include <iostream>
#include <vector>
#include <queue>

const int INF = 100000;

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int,int>>> g(n + 1);

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        g[a].push_back(std::make_pair(c, b));
        g[b].push_back(std::make_pair(c, a));
    }

    std::vector<int> d(n + 1, INF);
    d[1] = 0;
    int ansver = 0;
    std::priority_queue <std::pair<int,int>> q;
    q.push(std::make_pair(0, 1));
    while (!q.empty()) {
        int v = q.top().second,  cur_d = -q.top().first;
        q.pop();
        if (d[v] >= INF) break;
        if (cur_d > d[v])  continue;

        ansver += cur_d;
        for (auto& [len, to] : g[v]) {
            if (len < d[to]) {
                d[to] = len;
                q.push(std::make_pair(-d[to], to));
            }
        }
    }

    std::cout << ansver;
}
