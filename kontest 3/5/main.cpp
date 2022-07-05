#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

std::vector<int> bfs(int start, std::vector<std::vector<int>>& g) {
    std::vector<int> distance(g.size(), g.size() + 1);
    std::vector<int> visited(g.size());
    std::queue<int> q;
    q.push(start);
    distance[start] = 0;
    visited[start] = true;
    int v = 0;

    while(!q.empty()) {
        v = q.front();
        q.pop();
        for (auto& neig : g[v]) {
            if (!visited[neig]) {
                visited[neig] = true;
                q.push (neig);
                distance[neig] = distance[v] + 1;
            }
        }
    }
    return distance;
}

size_t extra_edges(int& s, int& t, std::vector<std::vector<int>>& g) {
    auto distsns1 = bfs(s, g);
    auto distsns2 = bfs(t, g);
    size_t counter = 0;
    for (int i = 1; i < g.size(); ++i) {
        for (auto& elem : g[i]) {
            if (distsns1[i] + distsns2[elem] + 1 != distsns1[t] &&
                distsns2[i] + distsns1[elem] + 1 != distsns1[t])
                ++counter;
        }
    }
    return counter / 2;
}

int main() {
    int v, e;
    std::cin >> v >> e;
    std::vector<std::vector<int>> table(v + 1);
    int top1 = 0, top2 = 0;
    for (int i = 0; i < e; ++i) {
        std::cin >> top1 >> top2;
        /*if (std::count(table[top1].begin(), table[top1].end(), top2) == 0 && top2 != top1) {
            table[top1].push_back(top2);
        }
        if (std::count(table[top2].begin(), table[top2].end(), top1) == 0 && top2 != top1) {
            table[top2].push_back(top1);
        }*/
        table[top1].push_back(top2);
        table[top2].push_back(top1);
    }

    int s, t;
    std::cin >> s >> t;

    std::cout << extra_edges(s, t, table) << "\n";
    return 0;
}

/*
 *8 11
1 2
1 6
2 3
2 8
3 4
4 5
4 8
5 6
5 7
6 8
7 8
 */