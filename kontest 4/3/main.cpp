#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const long long int INF = 300000000000;

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int,int>>> g(n + 1);

    for (int i = 0; i < m; ++i) {
        int top1, top2, t;
        std::cin >> top1 >> top2 >> t;
        g[top1].push_back(std::make_pair(t, top2));
        g[top2].push_back(std::make_pair(t, top1));
    }

    int a, b;
    std::cin >> a >> b;

    std::vector<long long int> d(n + 1, INF);
    d[a] = 0;
    std::priority_queue <std::pair<long long int,int>> q;
    q.push(std::make_pair(0, a));
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

    if (d[b] < INF)
        std::cout << d[b];
    else
        std::cout << -1;
}