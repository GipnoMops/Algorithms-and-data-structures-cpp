#include <iostream>
#include <vector>
#include <deque>

int bfs(int start, int end, std::vector<std::vector<std::pair<int, int>>>& g) {
    std::vector<int> distance(g.size(), g.size() + 1);
    std::deque<int> q;
    q.push_back(start);
    distance[start] = 0;
    int v = 0;

    while(!q.empty() /*&& v != end*/) {
        v = q.front();
        q.pop_front();
        for (auto& [neig, weight] : g[v]) {
            if (distance[v] + weight < distance[neig]) {
                distance[neig] = distance[v] + weight;
                if (weight == 1)
                    q.push_back(neig);
                else
                    q.push_front(neig);
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
    int n, m;
    std::vector<std::vector<std::pair<int, int>>> table(n + 1);
    std::cin >> n >> m;
    for (size_t i = 0; i < m; ++i) {
        int p;
        std::cin >> p;
        for (size_t j = 0; j < p; ++j) {

        }
    }
    return 0;
}
