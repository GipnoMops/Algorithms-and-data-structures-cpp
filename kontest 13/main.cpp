/*#include <vector>
#include <cstring>

const int MAXN = 500;
int n, g[MAXN][MAXN];
int best_cost = 1000000000;
std::vector<int> best_cut;


void mincut() {
    std::vector<int> v[MAXN];
    for (int i = 0; i < n; ++i)
        v[i].assign(1, i);
    int w[MAXN];
    bool exist[MAXN], in_a[MAXN];
    memset(exist, true, sizeof exist);
    for (int ph = 0; ph < n - 1; ++ph) {
        memset(in_a, false, sizeof in_a);
        memset(w, 0, sizeof w);
        for (int it = 0, prev; it < n - ph; ++it) {
            int sel = -1;
            for (int i = 0; i < n; ++i)
                if (exist[i] && !in_a[i] && (sel == -1 || w[i] > w[sel]))
                    sel = i;
            if (it == n - ph - 1) {
                if (w[sel] < best_cost)
                    best_cost = w[sel], best_cut = v[sel];
                v[prev].insert(v[prev].end(), v[sel].begin(),
                               v[sel].end());
                for (int i = 0; i < n; ++i)
                    g[prev][i] = g[i][prev] += g[sel][i];
                exist[sel] = false;
            } else {
                in_a[sel] = true;
                for (int i = 0; i < n; ++i)
                    w[i] += g[sel][i];
                prev = sel;
            }
        }
    }
}*/


#include <iostream>
#include <algorithm>
#include <vector>

bool compare(std::vector<char>& x, std::vector<char>& y) {
    auto i = x.begin(), j = y.begin();
    do {
        if (*i == ')' && *j == '[') return false;
        if (*i == '[' && *j == ')') return true;
        if (*i > *j) return false;
        if (*i < *j) return true;
        ++i; ++j;
    } while (i != x.end() - 1 && j != y.end() - 1);
    return false;
}

void rec(std::vector<char>& mas, int j, int N, int temp1,
         int temp2, std::vector<std::vector<char>>& answer) {
    if(j == N) answer.push_back(mas);
    else {
        int t1 = 0, t2 = 0, i, fl = 1;
        for(i = j - 1; fl && i >= 0; --i) {
            if (mas[i] == '(') --t1;
            if (mas[i] == '[') --t2;
            if (mas[i] == ')') ++t1;
            if (mas[i] == ']') ++t2;
            if (t1 < 0 || t2 < 0) fl = 0;
        }

        if(fl) {
            mas[j] = '(';
            rec(mas, j + 1, N, temp1 + 1, temp2, answer);
            mas[j] = '[';
            rec(mas, j + 1, N, temp1, temp2 + 1, answer);
        } else {
            if(t1 < 0) {
                mas[j] = ')';
                rec(mas, j + 1, N, temp1, temp2, answer);
                if(temp1 + temp2 < N / 2) {
                    mas[j] = '(';
                    rec(mas, j + 1, N, temp1 + 1, temp2, answer);
                    mas[j] = '[';
                    rec(mas, j + 1, N, temp1, temp2 + 1, answer);
                }
            }

            if(t2 < 0) {
                mas[j] = ']';
                rec(mas, j + 1, N, temp1, temp2, answer);
                if(temp1 + temp2 < N / 2) {
                    mas[j]= '(';
                    rec(mas, j + 1, N, temp1 + 1, temp2, answer);
                    mas[j]= '[';
                    rec(mas, j + 1, N, temp1, temp2 + 1, answer);
                }
            }
        }
    }
}


int main() {
    int n;
    std::cin >> n;
    if (n == 0) return 0;
    std::vector<char> mas(n);
    std::vector<std::vector<char>> answe;
    mas[0] = '(';
    rec(mas, 1, n, 1, 0, answe);
    mas[0] = '[';
    rec(mas, 1, n, 0, 1, answe);
    std::sort(answe.begin(), answe.end(), compare);
    for (auto& vec : answe) {
        for (auto elem : vec) std::cout << elem;
        std::cout << "\n";
    }
    return 0;
}