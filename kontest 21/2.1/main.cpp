#include <vector>
#include <iostream>


bool try_kuhn (int v, std::vector<std::vector<int>>& g, std::vector<char>& used, std::vector<int>& mt) {
    if (used[v]) return false;
    used[v] = true;
    for (auto to : g[v]) {
        if (mt[to] == -1 || try_kuhn (mt[to], g, used, mt)) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}


int main() {
    int n, m;
    std::string name;
    std::cin >> m >> name;
    n = name.size();

    std::vector<std::vector<int>> g(n);
    std::vector<std::string> cubes;
    for (int i = 0; i < m; ++i) {
        std::string cube;
        std::cin >> cube;
        cubes.push_back(cube);
    }

   //for (const auto& elem : cubes) std::cout << elem << " ";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (cubes[j].find_first_of(name[i]) != std::wstring::npos) g[i].push_back(j);
        }
    }

    int counter = 0;
    std::vector<char> used;
    std::vector<int> mt(m, -1);
    for (int v = 0; v < n; ++v) {
        used.assign (n, false);
        if (try_kuhn(v, g, used, mt)) ++counter;
    }

    if (counter == n) {
        std::cout << "YES" << "\n";
        std::vector<std::pair<int, int>> answer;
        for (int i = 0; i < m; ++i) {
            if (mt[i] != -1) answer.emplace_back(mt[i] + 1, i + 1);
        }
        std::sort(answer.begin(), answer.end());
        //std::cout << answer.size();
        for (auto a : answer) {
            std::cout << a.second << " ";
        }
    } else std::cout << "NO";
}

// 16
// ASDFGHJQWERTCXBA
// BJKJSH
// TSSDFG
// SDFGFD
// XMCVKF
// RSDFCX
// CLKGMN
// AAAAAF
// WSGXDF
// ELKSDF
// QZCFWA
// SLKCXR
// GKJNFD
// JGSDCS
// FWELKD
// HLNGJS
// DSDFEW
