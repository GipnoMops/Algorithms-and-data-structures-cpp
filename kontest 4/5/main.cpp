#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const int INF = 1000001;

int main() {
    int n, m, k, c;
    std::cin >> n >> m >> k >> c;
    std::vector<std::pair<int, int>> citys;
    for (int i = 0; i < k; ++i) {
        int city;
        std::cin >> city;
        citys.push_back(std::make_pair(INF, city));
    }

    std::vector<std::vector<std::pair<int,int>>> g(n + 1);

    for (int i = 0; i < m; ++i) {
        int top1, top2, t;
        std::cin >> top1 >> top2 >> t;
        g[top1].push_back(std::make_pair(t, top2));
        g[top2].push_back(std::make_pair(t, top1));
    }

    std::vector<int> d(n + 1, INF);
    d[c] = 0;
    std::priority_queue <std::pair<int,int>> q;
    q.push(std::make_pair(0, c));
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

    for (auto& [len, city] : citys)
        len = d[city];

    std::sort(citys.begin(), citys.end());

    for (auto& [len, city] : citys)
        std::cout << city << " " << len << "\n";
}