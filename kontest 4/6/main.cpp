#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const int INF = 1000001;

int main() {
    int n, s, f, r;
    std::cin >> n >> s >> f >> r;

    std::vector<std::vector<std::pair<std::pair<int, int>, int>>> g(n + 1);

    for (int i = 0; i < r; ++i) {
        int top1, t1, top2, t2;
        std::cin >> top1 >> t1 >> top2 >> t2;
        g[top1].push_back(std::make_pair(std::make_pair(t1, t2), top2));
    }

    std::vector<int> d(n + 1, INF);
    d[s] = 0;
    std::priority_queue <std::pair</*std::pair<int, int>*/ int, int>> q;
    q.push(std::make_pair(0, s));
    while (!q.empty()) {
        int v = q.top().second,  cur_d = -q.top().first;
        q.pop();
        if (d[v] >= INF) break;
        if (cur_d > d[v])  continue;

        for (auto& [time, to] : g[v]) {
            if (d[v] <= time.first && time.second < d[to]) {
                d[to] = time.second;
                q.push(std::make_pair(-d[to], to));
            }
        }
    }

    if (d[f] < INF)
        std::cout << d[f];
    else
        std::cout << -1;
}
