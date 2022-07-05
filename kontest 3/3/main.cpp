#include <iostream>
#include <vector>
#include <queue>


size_t bfs(size_t start, size_t n, std::vector<std::vector<size_t>>& g) {
    std::vector<size_t> distance(g.size(), g.size() + 1);
    std::vector<size_t> visited(g.size());
    std::queue<size_t> q;
    q.push(start);
    distance[start] = 0;
    visited[start] = true;
    size_t v = 0;

    size_t counter = 0;

    while(!q.empty() && counter < n * n) {
        int v = q.front();
        q.pop();
        if (v <= n * n)
            ++counter;

        for (auto& neig : g[v]) {
            if (!visited[neig]) {
                visited[neig] = true;
                q.push (neig);
                distance[neig] = distance[v] + 1;
            }
        }
    }

    size_t ansver = g.size() + 1;
    for (size_t i = 1; i <= n * n; ++i) {
        ansver = std::min(ansver, distance[i]);
    }
    return ansver;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<size_t> exit;
    std::vector<std::vector<size_t>> table(n * n * n);
    std::vector<size_t> delet;
    size_t start;
    char top;
    for (size_t i = 1; i <= n * n * n; ++i) {
        std::cout << i << "\n";
        std::cin >> top;
        if (top == '#')
            delet.push_back(i);
        else {
            if ((i % n) != 0) {
                table[i + 1].push_back(i);
            }
            if ((i % n) != 1) {
                table[i - 1].push_back(i);
            }
            if (i > n) {
                table[i - n].push_back(i);
            }
            if ((i + n) <= n * n * n) {
                table[i + n].push_back(i);
            }
            if (top == 'S') {
                start = i;
            }
        }
    }
    /*for (auto& elem : delet) {
        table[elem].clear();
    }*/
    std::cout << "end";
    return 0;
}

/*
1  2  3  4
5  6  7  8
9  10 11 12
13 14 15 16
 */