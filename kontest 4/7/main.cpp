#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <map>

const int INF = 999999999;

std::vector<int> dejkstra (std::vector<std::vector<std::pair<std::pair<int, int>, int>>>& g, int& s, int& t) {
    std::vector<int> d(g.size(), INF);
    d[s] = t;
    std::priority_queue <std::pair<int, int>> q;
    q.push(std::make_pair(0, s));
    while (!q.empty()) {
        int v = q.top().second,  cur_d = -q.top().first;
        q.pop();
        if (d[v] >= INF) break;
        if (cur_d > d[v])  continue;

        for (auto& [time, to] : g[v]) {
            if (d[v] % time.second == 0 && d[v] + time.first < d[to]) {
                d[to] = d[v] + time.first;
                q.push(std::make_pair(-d[to], to));
            } else if (d[v] + time.second - (d[v] % time.second) + time.first < d[to]) {
                d[to] = d[v] + time.second - (d[v] % time.second) + time.first;
                q.push(std::make_pair(-d[to], to));
            }
        }
    }

    return d;
}

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<std::pair<std::pair<int, int>, int>>> g(n + 1);

    for (int i = 0; i < k; ++i) {
        int top1, top2, period, time;
        std::cin >> top1 >> top2 >> period >> time;
        g[top1].push_back(std::make_pair(std::make_pair(time, period), top2));
    }

    int m;
    std::cin >> m;
    std::vector<int> map;
    for (int i = 0; i < m; ++i) {
        int top;
        std::cin >> top;
        map.push_back(top);
    }

    //std::map<int, std::vector<int>> distans;

    int ansver = 0;
    /*for (int i = 0; i < map.size() - 1; ++i) {
        if (distans.find(map[i]) != distans.end()) {
            int len = distans[map[i]][map[i + 1]];
            if (len >= INF) {
                ansver = -1;
                break;
            }
            ansver = len;
        } else {
            distans[map[i]] = dejkstra(g, map[i], ansver);
            int len = distans[map[i]][map[i + 1]];
            if (len >= INF) {
                ansver = -1;
                break;
            }
            ansver = len;
        }
    }*/

    for (int i = 0; i < map.size() - 1; ++i) {
        auto dis = dejkstra(g, map[i], ansver);
        if (dis[map[i + 1]] >= INF) {
            ansver = -1;
            break;
        }
        ansver = dis[map[i + 1]];;
    }

    std::cout << ansver << "\n";
}
