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
    for (auto& elem : distance) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
    return ansver;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<size_t> exit;
    std::vector<std::vector<size_t>> table(n * n * n + 1);
    std::vector<size_t> delet;
    size_t start;
    char top;
    for (size_t i = 1; i <= n * n * n; ++i) {
        std::cout << i << " ";
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
            if ((i - n * n) > 0) {
                std::cout << "da ";
                table[i - n * n].push_back(i);
            }/*
            if ((i + n * n) <= n * n * n) {
                table[i + n * n].push_back(i);
            }*/
            if (top == 'S') {
                start = i;
            }
        }
    }

    for (size_t i = 1; i < table.size(); ++i) {
        std::cout << i << ": ";
        for (auto b : table[i]) {
            std::cout << b << " ";
        }
        std::cout << "\n";
    }
    std::cout << bfs(start, n, table);
    return 0;
}

/*
1  2  3  4
5  6  7  8
9  10 11 12
13 14 15 16

17 18 19 20
21 22 23 24
25 26 27 28
29 30 31 32

33 34 35 36
37 38 39 40
41 42 43 44
45 46 47 48



1  2  3
4  5  6
7  8  9

10 11 12
13 14 15
16 17 18

19 20 21
22 23 24
25 26 27
 */