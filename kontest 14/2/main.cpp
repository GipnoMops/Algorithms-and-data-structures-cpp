#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
std::set<int> Tops;

bool NextSet(std::vector<int>& a, int n, int m) {
    int k = m;
    for (int i = k - 1; i >= 0; --i)
        if (a[i] < n - k + i + 1) {
            ++a[i];
            for (int j = i + 1; j < k; ++j) a[j] = a[j - 1] + 1;
            return true;
        }
    return false;
}

void Print(std::vector<int>& a, int m, int& anwer,
           std::vector<std::vector<int>>& table, std::vector<int>& selected) {
    std::set<int> remains = Tops;
    int temp = 0;
    for (int i = 0; i < m; ++i) remains.erase(a[i]);
    for (int i = 0; i < m; ++i)
        for (auto elem_2 : remains)
            temp += table[a[i]][elem_2];
    if (temp > anwer) {
        anwer = temp;
        auto it_end = a.begin();
        std::advance(it_end, m);
        selected.clear();
        selected.resize(m);
        std::copy(a.begin(), it_end, selected.begin());
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> table(n + 1 ,std::vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        Tops.insert(i);
        for (int j = 1; j <= n; ++j) {
            int weight;
            std::cin >> weight;
            table[i][j] = weight;
        }
    }

    int m = (n + 1) / 2, anwer = 0;
    std::vector<int> a(n), selected(m);
    for (int i = 0; i < n; ++i) a[i] = i + 1;
    Print(a, m, anwer, table, selected);
    if (n >= m) while (NextSet(a, n, m)) Print(a, m, anwer, table, selected);

    std::cout << anwer << "\n";
    if (anwer > 0) {
        std::vector<int> print_vec(n + 1, 1);
        for (auto elem : selected) print_vec[elem] = 2;
        for (int i = 1; i <= n; ++i) std::cout << print_vec[i] << " ";
    } else {
        throw;
    }
    return 0;
}
