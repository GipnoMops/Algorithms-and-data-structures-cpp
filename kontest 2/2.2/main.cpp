#include <iostream>
#include <vector>
#include <algorithm>
//#include <utility>

void dfs (size_t now, std::vector<std::vector<std::pair<size_t, size_t>>>& g, size_t p,
          std::vector<bool>& used, size_t& timer,
          std::vector<size_t>& tin, std::vector<size_t>& fup) {
    used[now] = true;
    tin[now] = fup[now] = timer++;
    for (auto& [neig, order] : g[now]) {
        if (neig == p)  continue;
        if (used[neig])
            fup[now] = std::min(fup[now], tin[neig]);
        else {
            dfs(neig, g, now, used, timer, tin, fup);
            fup[now] = std::min(fup[now], fup[neig]);
            if (fup[neig] > tin[now])
                std::cout << order << "\n";
        }
    }
}

void find_bridges(std::vector<std::vector<std::pair<size_t, size_t>>>& g) {
    std::vector<bool> used(g.size(), false);
    std::vector<size_t> tin(g.size());
    std::vector<size_t> fup(g.size());

    for (size_t i = 1; i < g.size(); ++i) {
        size_t timer = 0;
        if (!used[i])
            dfs(i, g, -1, used, timer, tin, fup);
    }

}

int main() {
    size_t v, e;
    std::cin >> v >> e;
    std::vector<std::vector<std::pair<size_t, size_t>>> table(v + 1);
    size_t top1 = 0, top2 = 0;
    for (size_t i = 0; i < e; ++i) {
        std::cin >> top1 >> top2;
        if (std::count(table[top1].begin(), table[top1].end(), top2) == 0 && top2 != top1) {
            table[top1].push_back(std::make_pair(top2, i + 1));
        }
        if (std::count(table[top2].begin(), table[top2].end(), top1) == 0 && top2 != top1) {
            table[top2].push_back(std::make_pair(top1, i + 1));
        }
    }

    //find_bridges(table);
    return 0;
}
