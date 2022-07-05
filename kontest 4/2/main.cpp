#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>

const int INF = 10001;

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

    std::vector<int> d(n + 1, INF), p(n + 1);
    d[s] = 0;
    std::priority_queue <std::pair<int,int>> q;
    q.push(std::make_pair(0, s));
    int v, cur_d;
    while (!q.empty()) {
        v = q.top().second;
        cur_d = -q.top().first;
        q.pop();
        if (d[v] >= INF) break;
        if (cur_d > d[v])  continue;

        for (auto& [len, to] : g[v]) {
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push(std::make_pair(-d[to], to));
            }
        }
    }

    g.clear();

    if (d[f] < INF) {
        std::deque<int> ansver;
        ansver.push_front(f);
        int top = f;
        while (true) {
            ansver.push_front(p[top]);
            top = p[top];
            if (top == s)
                break;
        }

        for (auto& elem : ansver) {
            std::cout << elem << " ";
        }
    } else
        std::cout << -1;
}
